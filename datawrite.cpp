#include "datawrite.h"
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




