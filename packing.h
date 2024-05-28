#ifndef PACKING_H
#define PACKING_H

#include "piece.h"
#include <vector>

namespace MyNest{


class Packing
{
public:
    static Packing* packing;
    static Packing* getInstance();

    static box_t bin;
    static std::vector<Piece> pieces;
    static std::vector<std::vector<Piece>> piecesCache;

    inline std::string getNfpKey(const Piece &A,const Piece &B);
    inline std::string getIfrKey(const Piece &A);

    point_t findMostLeftPoint(std::vector<ring_t> &rings);
    void preprocess();
    int getNfps();
    int getIfrs();
    double run();

private:
    Packing();
    Packing(const Packing&) = delete;
    void operator=(const Packing&) = delete;
};
}


#endif // NEST_H
