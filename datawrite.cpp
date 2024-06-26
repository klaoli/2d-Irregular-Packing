#include "datawrite.h"
#include "dataloader.h"
#include "parameters.h"
#include <fstream>

using namespace MyNest;

DataWrite* DataWrite::datawriter = nullptr;

DataWrite::DataWrite()
{

}

DataWrite* DataWrite::getInstance() {
    if (datawriter == nullptr) {
        datawriter = new DataWrite;
    }
    return datawriter;
}


void DataWrite::writeNfps(const std::unordered_map<std::string, polygon_t>& nfps) const {
    std::ofstream outf;     // 写入csv文件
    outf.open(Parameters::nfpPath, std::ios::out);
    if (!outf) {
        std::cerr << "Error: Failed to open file." << std::endl;
        return;
    }
    outf << "Key,Outers,Inners" << std::endl;
    for (auto &nfpPair : DataLoader::nfpsCache) {
        const auto& nfp = nfpPair.second;
         outf << nfpPair.first << ",";  // 写入键
         for (const auto& point : nfp.outer()) {    // 写入外环坐标
             outf << point.x() << " " << point.y() << " ";
         }
         outf << ","; // 分隔符
         for (const auto& inner : nfp.inners()) {   // 写入内环坐标
             for (const auto& point : inner) {
                 outf << point.x() << " " << point.y() << " ";
             }
         }
         outf << std::endl; // 换行
    }
    outf.close();
}

void DataWrite::writeIfrs(const std::unordered_map<std::string, polygon_t>& nfps) const {
    std::ofstream outf;     // 写入csv文件
    outf.open(Parameters::nfpPath, std::ios::out);
    if (!outf) {
        std::cerr << "Error: Failed to open file." << std::endl;
        return;
    }
    outf << "Key,Outers,Inners" << std::endl;
    for (auto &ifrPair : DataLoader::ifrsCache) {
        const auto& ifr = ifrPair.second;
         outf << ifrPair.first << ",";  // 写入键
         for (const auto& point : ifr.outer()) {    // 写入外环坐标
             outf << point.x() << " " << point.y() << " ";
         }
         outf << ","; // 分隔符
         for (const auto& inner : ifr.inners()) {   // 写入内环坐标
             for (const auto& point : inner) {
                 outf << point.x() << " " << point.y() << " ";
             }
         }
         outf << std::endl; // 换行
    }
    outf.close();
}

void DataWrite::plotPiece(Piece &piece) const {
    std::ofstream svg("piece.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);
    mapper.add(piece.polygon);
    mapper.map(piece.polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
}


void DataWrite::plotPieces(std::vector<Piece> &pieces) const{
    std::ofstream svg("pieces.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);
    for (auto& piece : pieces){
        mapper.add(piece.polygon);
        mapper.map(piece.polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
    }
}


void DataWrite::plotPieces(box_t &bin, std::vector<Piece> &pieces) const {
    std::ofstream svg("packing.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);
    mapper.add(bin);
    mapper.map(bin,"fill-opacity:0;fill:rgb(255,255,255);stroke:rgb(0,0,0);stroke-width:0.1");

    for (auto& piece : pieces){
        mapper.add(piece.polygon);
        mapper.map(piece.polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
    }
}

void DataWrite::plotPolygon(polygon_t &polygon) const {
    std::ofstream svg("polygon.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);

    mapper.add(polygon);
    mapper.map(polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
}


void DataWrite::plotPolygons(std::vector<polygon_t> &polygons) const {
    std::ofstream svg("polygons.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);
    for (auto& polygon : polygons){
        mapper.add(polygon);
        mapper.map(polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
    }
}



void DataWrite::plotNoFitPolygon(Piece &pieceA, Piece &pieceB) const {

}



void DataWrite::plotNoFitPolygon(polygon_t &polyA, polygon_t &polyB) const {

}


void DataWrite::plotInnerFitPolygon(box_t &bin, polygon_t &polygon)const {

}


void DataWrite::plotInnerFitPolygon(box_t &bin, Piece &piece) const {

}




