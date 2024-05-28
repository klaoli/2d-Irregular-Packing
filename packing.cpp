#include "packing.h"
#include "parameters.h"
#include "dataloader.h"
#include "nofitpolygon.h"

using namespace MyNest;
Packing* Packing::packing = nullptr;

box_t Packing::bin;
std::vector<Piece> Packing::pieces;
std::vector<std::vector<Piece>> Packing::piecesCache;


Packing::Packing() {

}


Packing* Packing::getInstance() {
    if (packing == nullptr) {
        packing = new Packing;
    }
    return packing;
}

std::string Packing::getNfpKey(const Piece &A,const Piece &B) {
    return std::to_string(A.typeId) + "_" +std::to_string(A.rotation) + "-" +
            std::to_string(B.typeId) + "-" +std::to_string(B.rotation);
}

std::string Packing::getIfrKey(const Piece &A) {
    return std::to_string(A.typeId) + "_" +std::to_string(A.rotation);
}


void Packing::preprocess() {
    // 放缩  简化  平移到原点
    for (auto& piece : pieces) {
        piece.offset(0);
        piece.clean();
        double dx = -piece.polygon.outer().front().x();
        double dy = -piece.polygon.outer().front().y();
        piece.translate(dx, dy);
    }
    piecesCache.clear();
    int deltaAngle = 360 / Parameters::orientations;
    for (int angle = 0; angle < 360; angle += deltaAngle) {
        std::vector<Piece> temp;
        for (auto piece : pieces) {
            piece.rotate((double)angle);
            piece.offset(0);
            piece.clean();
            double dx = -piece.polygon.outer().front().x();
            double dy = -piece.polygon.outer().front().y();
            piece.translate(dx, dy);
            temp.push_back(piece);
        }
        piecesCache.push_back(temp);
    }
}


int Packing::getNfps() {
    if (DataLoader::nfpsCache.size() != 0){
        return DataLoader::nfpsCache.size();
    }

    std::vector<Piece> allRotationPieces;     // 将所有角度的零件放入容器中，便于遍历
    for (int i = 0; i < piecesCache.size(); ++i) {
        for (int j = 0; j < piecesCache[i].size(); ++j)
            allRotationPieces.push_back(piecesCache[i][j]);
    }

    static NFP* nfpGenerator = NFP::getInstance();
    for (int i = 0; i < allRotationPieces.size(); i++) {
        for (int j = i; j < allRotationPieces.size(); j++) {

            std::string nfpKey = getNfpKey(allRotationPieces[j], allRotationPieces[i]); // no fit polygon
            if (DataLoader::nfpsCache.find(nfpKey) == DataLoader::nfpsCache.end()) {

                polygon_t nfp = nfpGenerator->minkowskiDif(allRotationPieces[j].polygon, allRotationPieces[i].polygon);

                DataLoader::nfpsCache.insert(std::pair<std::string, polygon_t>(nfpKey, nfp));
            }

            nfpKey = getNfpKey(allRotationPieces[i], allRotationPieces[j]);
            if (DataLoader::nfpsCache.find(nfpKey) == DataLoader::nfpsCache.end()) {

                polygon_t nfp = nfpGenerator->minkowskiDif(allRotationPieces[i].polygon, allRotationPieces[j].polygon);

                DataLoader::nfpsCache.insert(std::pair<std::string, polygon_t>(nfpKey, nfp));
            }
        }
    }
    return DataLoader::nfpsCache.size();
}


int Packing::getIfrs() {
    if (DataLoader::ifrsCache.size() != 0){
        return DataLoader::ifrsCache.size();
    }

    std::vector<Piece> allRotationPieces;     // 将所有角度的零件放入容器中，便于遍历
    for (int i = 0; i < piecesCache.size(); ++i) {
        for (int j = 0; j < piecesCache[i].size(); ++j)
            allRotationPieces.push_back(piecesCache[i][j]);
    }

    static NFP* nfpGenerator = NFP::getInstance();
    for (int i = 0; i < allRotationPieces.size(); i++) {

        std::string ifrKey = getIfrKey(allRotationPieces[i]);  // 内接临界矩形

        if (DataLoader::nfpsCache.find(ifrKey) == DataLoader::nfpsCache.end()) {
            polygon_t ifr = nfpGenerator->generateIfr(DataLoader::bin, allRotationPieces[i].polygon);
            DataLoader::nfpsCache.insert(std::pair<std::string, polygon_t>(ifrKey, ifr));
        }
    }
    return DataLoader::ifrsCache.size();
}

point_t Packing::findMostLeftPoint(std::vector<ring_t> &finalNfp) {
    point_t mostLeftPoint(Parameters::MAXDOUBLE, Parameters::MAXDOUBLE);

    for (auto &poly : finalNfp) {
        for (int i = 0; i < poly.size(); i++) {
            if (poly[i].x() < mostLeftPoint.x()) {
                mostLeftPoint.set<0>(poly[i].x());
                mostLeftPoint.set<1>(poly[i].y());
            }
            if (poly[i].x() == mostLeftPoint.x() && poly[i].y() < mostLeftPoint.y()) {
                mostLeftPoint.set<1>(poly[i].y());
            }
        }
    }
    return mostLeftPoint;
}

double Packing::run() {
    std::vector<Piece> placedPieces;
    std::vector<Vector> placedVectors;

    for (int i = 0; i < pieces.size(); ++i) {
        std::string ifpKey = getIfrKey(pieces[i]);
        polygon_t ifr = DataLoader::nfpsCache[ifpKey];

        Vector curVector;
        if (placedPieces.size() == 0) {  // 排放第一个
            curVector.x = Parameters::MAXDOUBLE;
            point_t referPoint = pieces[i].polygon.outer().front();   // 参考点
            for (auto &point : ifr.outer()) {
                if (point.x() - referPoint.x() < curVector.x) {  // 寻找 ifr 最左边的位置
                    curVector = Vector(point.x() - referPoint.x(), point.y() - referPoint.y());
                }
            }
            placedPieces.push_back(pieces[i]);
            placedVectors.push_back(curVector);
            continue;
        }

#pragma region ClipperExecute
        Paths clipperUnionNfp;
        Paths clipperFinalNfp;
        ClipperLib::Clipper clipperUnion;
        ClipperLib::Clipper clipperDifference;
        //bin_nfp 转换成 clipper paths，即 clipperBinNfp.
        static GeometryConvert* converter = GeometryConvert::getInstance();
        Paths clipperBinNfp = converter->boost2ClipperPolygon(ifr);

        // nfp 转换成 clipper paths, 求并集得到 clipperUnionNfp.
        for (int j = 0; j < placedPieces.size(); ++j) {
            std::string key = getNfpKey(placedPieces[j], pieces[i]);
            Paths clipperNfp = converter->boost2ClipperPolygon(DataLoader::nfpsCache[key]);
            for (auto & path : clipperNfp) {
                for (auto & point : path) {
                    point.X += static_cast<cInt>(placedVectors[j].x * Parameters::scaleRate);
                    point.Y += static_cast<cInt>(placedVectors[j].y * Parameters::scaleRate);
                }
            }
            clipperUnion.AddPaths(clipperNfp, ClipperLib::PolyType::ptSubject, true);
        }
        if (!clipperUnion.Execute(ClipperLib::ClipType::ctUnion, clipperUnionNfp, ClipperLib::PolyFillType::pftNonZero, ClipperLib::PolyFillType::pftNonZero)) {
            std::cout << "clipperUnion Execute Failed: " << pieces[i].id << std::endl;
            continue;
        }

        //clipperBinNfp 经 clipperUnionNfp 裁剪（求差集）得到 clipperFinalNfp.
        clipperDifference.AddPaths(clipperBinNfp, ClipperLib::PolyType::ptSubject, true);
        clipperDifference.AddPaths(clipperUnionNfp, ClipperLib::PolyType::ptClip, true);
        if (!clipperDifference.Execute(ClipperLib::ClipType::ctDifference, clipperFinalNfp, ClipperLib::PolyFillType::pftEvenOdd, ClipperLib::PolyFillType::pftNonZero)) {
            std::cout << "clipperDifference Execute Failed: " << pieces[i].id << std::endl;
            continue;
        }

        //clean clipperFinalNfp
        CleanPolygons(clipperFinalNfp, 0.0001 * Parameters::scaleRate);

        clipperFinalNfp.erase(std::remove_if(clipperFinalNfp.begin(), clipperFinalNfp.end(),
            [](const Path &path) {
            return path.size() < 3 || ClipperLib::Area(path) < 0.1 * Parameters::scaleRate * Parameters::scaleRate;
        }), clipperFinalNfp.end());

        if (clipperFinalNfp.empty()) {
            std::cout << "clipperFinalNfp is empty: " << pieces[i].id << std::endl;
            continue;
        }
#pragma endregion ClipperExecute


#pragma region Placement
        std::vector<ring_t> finalNfp;    // 在 final_nfp 的每个顶点上放置零件
        finalNfp.reserve(clipperFinalNfp.size());
        for (auto & path : clipperFinalNfp) {
            finalNfp.push_back(converter->clipper2BoostRing(path));
        }
        point_t mostLeftPoint = findMostLeftPoint(finalNfp);  // 计算最左点
        point_t referPoint = pieces[i].polygon.outer().front();
        curVector = Vector(mostLeftPoint.x() - referPoint.x(), mostLeftPoint.y() - referPoint.y());
        placedPieces.push_back(pieces[i]);
        placedVectors.push_back(curVector);
#pragma endregion Placement
    }

    double minX = Parameters::MAXDOUBLE, maxX = 0;
    for (int i = 0; i < placedPieces.size(); ++i) {
        placedPieces[i].translate(placedVectors[i].x, placedVectors[i].x);
        if (placedPieces[i].bounding.min_corner().x() < minX) {
            minX = placedPieces[i].bounding.min_corner().x();
        }

        if (placedPieces[i].bounding.max_corner().x() > maxX) {
            maxX = placedPieces[i].bounding.max_corner().x();
        }
    }
    return maxX - minX;

}
