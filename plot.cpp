#include "plot.h"
#include <fstream>
using namespace MyNest;

Plot* Plot::plot = nullptr;

Plot::Plot(){

}


Plot* Plot::getInstance() {
    if(plot == nullptr) {
        plot = new Plot;
    }

    return plot;
}


void Plot::plotPiece(Piece &piece) const {
    std::ofstream svg("piece.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);
    mapper.add(piece.polygon);
    mapper.map(piece.polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
}


void Plot::plotPieces(std::vector<Piece> &pieces) const{
    std::ofstream svg("pieces.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);
    for (auto& piece : pieces){
        mapper.add(piece.polygon);
        mapper.map(piece.polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
    }
}


void Plot::plotPieces(box_t &bin, std::vector<Piece> &pieces) const {
    std::ofstream svg("packing.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);
    mapper.add(bin);
    mapper.map(bin,"fill-opacity:0;fill:rgb(255,255,255);stroke:rgb(0,0,0);stroke-width:0.1");

    for (auto& piece : pieces){
        mapper.add(piece.polygon);
        mapper.map(piece.polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
    }
}

void Plot::plotPolygon(polygon_t &polygon) const {
    std::ofstream svg("polygon.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);

    mapper.add(polygon);
    mapper.map(polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
}


void Plot::plotPolygons(std::vector<polygon_t> &polygons) const {
    std::ofstream svg("polygons.svg");
    bg::svg_mapper<point_t> mapper(svg, 800, 800);
    for (auto& polygon : polygons){
        mapper.add(polygon);
        mapper.map(polygon, "fill-opacity:0.3;fill:rgb(200,200,200);stroke:rgb(0,0,0);stroke-width:0.1");
    }
}



void Plot::plotNoFitPolygon(Piece &pieceA, Piece &pieceB) const {

}



void Plot::plotNoFitPolygon(polygon_t &polyA, polygon_t &polyB) const {

}


void Plot::plotInnerFitPolygon(box_t &bin, polygon_t &polygon)const {

}


void Plot::plotInnerFitPolygon(box_t &bin, Piece &piece) const {

}
