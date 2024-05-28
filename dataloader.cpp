#include "dataloader.h"

#include <string>
#include <sstream>
#include <fstream>
#include "parameters.h"

using namespace MyNest;

DataLoader* DataLoader::dataLoader = nullptr;

box_t DataLoader::bin;
std::vector<Piece> DataLoader::pieces;
std::unordered_map<std::string, polygon_t> DataLoader::nfpsCache;
std::unordered_map<std::string, polygon_t> DataLoader::ifrsCache;

DataLoader::DataLoader() {

}

DataLoader* DataLoader::getInstance() {
    if (dataLoader == nullptr){
        dataLoader = new DataLoader;
    }
    return dataLoader;
}

void DataLoader::dataLoadFromTxt() {

    std::string line;
    std::vector<double> v1, v2;   // 存储第一行数据、第二行数据
    std::vector< std::vector<double> > v3;  // 第三行到最后一行
    std::ifstream fin(Parameters::piecePath);

    std::getline(fin, line);    // 获取第一行数据
    std::stringstream ss;
    ss << line;
    if (!ss.eof()) {
        double temp;
        while (ss >> temp)
            v1.push_back(temp);
    }
    // v1数组的检查

    std::getline(fin, line);    // 读取第二行数据
    ss.clear();
    ss << line;
    if (!ss.eof()) {
        double temp;
        while (ss >> temp)
            v2.push_back(temp);
    }
    // v2数组的检查

    while (getline(fin, line)) {    // 第三行至最后一行
        ss.clear();
        std::vector<double> tmp;
        ss << line;
        if (!ss.eof()) {
            double temp;
            while (ss >> temp)
                tmp.push_back(temp);
        }
        v3.push_back(tmp);
    }
    fin.close();

    int numPolys = 0;    // 多边形的数量
    for (int i = 1; i < v1.size(); ++i){
        numPolys += v1[i];
    }

    bg::set<bg::max_corner, 0>(bin, v2[0] * Parameters::polygonScaleRate);
    bg::set<bg::max_corner, 1>(bin, v2[1] * Parameters::polygonScaleRate);
    int typeId = 0;
    for (int i = 0; i < numPolys; ++i) {
        Piece piece;
        polygon_t polygon;
        for (int j = 1; j < v3[i].size(); j += 2) {
            point_t p(v3[i][j]*Parameters::polygonScaleRate, v3[i][j + 1]*Parameters::polygonScaleRate);
            polygon.outer().push_back(p);
        }
        bg::correct(polygon); // 形成闭合多边形, 多边形逆时针化
        piece.id = i;
        piece.polygon = polygon;
        piece.area = bg::area(polygon);
        piece.bounding = piece.getEnvelope();
        if(i == 0) {
            piece.typeId = typeId;
            typeId++;
            continue;
        }
        for (int j = 0; j < pieces.size(); ++j){
            if (bg::equals(piece.polygon, pieces[j].polygon)) {
                piece.typeId = pieces[j].typeId;
                break;
            }
        }
        if (piece.typeId == -1) {
            piece.typeId = typeId;
            typeId++;
        }
        pieces.push_back(piece);
    }
}

void DataLoader::dataLoadFromTxt2() {
    std::string line;
    std::vector<double> v1, v2;   //第一行数据
    std::vector< std::vector<double> > v3;  //第三行到最后一行

    std::ifstream fin(Parameters::piecePath);

    std::getline(fin, line);
    std::stringstream ss;
    ss << line;
    if (!ss.eof()) {
        double temp;
        while (ss >> temp)
            v1.push_back(temp);
    }

    std::getline(fin, line);
    ss.clear();
    ss << line;
    if (!ss.eof()) {
        double temp;
        while (ss >> temp)
            v2.push_back(temp);
    }


    while (getline(fin, line)) {
        std::vector<double> tmp;
        ss.clear();
        ss << line;
        if (!ss.eof()) {
            double temp;
            while (ss >> temp)
                tmp.push_back(temp);
        }
        v3.push_back(tmp);
    }
    fin.close();

    int numPolys = 0;    //多边形的数量
    for (int i = 1; i < v1.size(); i++){
        numPolys += v1[i];
    }

    bin.max_corner().set<0>(v2[0] * Parameters::polygonScaleRate);
    bin.max_corner().set<0>(v2[1] * Parameters::polygonScaleRate);

    for (int i = 0; i < numPolys; i++) {
        Piece piece;
        polygon_t polygon;
        int mid = v3[i].size() / 2 + 1;
        for (int j = 1; j <= v3[i].size() / 2; j++) {
            point_t p(v3[i][j] * 10, v3[i][mid] * 10);
            mid++;
            polygon.outer().push_back(p);
        }
        bg::correct(polygon);

        piece.polygon = polygon;
        piece.id = i;
        piece.rotation = 0;
        if((piece.area = piece.signedArea()) < 0) {
            piece.area = -piece.area;
            std::reverse(piece.polygon.outer().begin(), piece.polygon.outer().end());
        }
        piece.bounding = piece.getEnvelope();
        pieces.push_back(piece);
        if (i == 0){
            piece.typeId = 1;
            pieces.push_back(piece);
            continue;
        }
        for (int j = 0; j < pieces.size(); ++j){
            if(bg::equals(pieces[j].polygon, piece.polygon)){
                piece.typeId = pieces[j].typeId;
                pieces.push_back(piece);
                break;
            }
        }
    }
}
