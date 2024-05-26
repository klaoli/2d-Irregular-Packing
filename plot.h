#ifndef PLOT_H
#define PLOT_H

#include "piece.h"

namespace MyNest {

class Plot
{

public:
    static Plot* plot;
    static Plot* getInstance();

    void plotPiece(Piece &piece) const;
    void plotPieces(std::vector<Piece> &pieces) const;
    void plotPieces(box_t &bin, std::vector<Piece> &pieces) const;

    void plotPolygon(polygon_t &polygon) const;
    void plotPolygons(std::vector<polygon_t> &polygons) const;

    void plotNoFitPolygon(Piece &pieceA, Piece &pieceB) const;
    void plotNoFitPolygon(polygon_t &polyA, polygon_t &polyB) const;

    void plotInnerFitPolygon(box_t &bin, polygon_t &polygon)const;
    void plotInnerFitPolygon(box_t &bin, Piece &piece) const;

private:
    Plot();
    Plot(const Plot&) = delete;
    void operator=(const Plot&) = delete;

};

}



#endif // PLOT_H
