#ifndef PACKING_H
#define PACKING_H

#include "piece.h"
#include <vector>
#include <unordered_map>

namespace MyNest{


class Packing
{
public:
    static Packing* packing;
    static Packing* getInstance();

    static box_t bin;
    static std::vector<Piece> pieces;
    static std::vector<std::vector<Piece>> piecesCache;
    static std::unordered_map<std::string, polygon_t> nfpsCache;

    inline std::string getNfpKey(const Piece &A,const Piece &B);
    inline std::string getIfrKey(const Piece &A);
    void preprocess();
    void getNfps();
    void getIfrs();
    void run();

private:
    Packing();
    Packing(const Packing&) = delete;
    void operator=(const Packing&) = delete;
};
}


#endif // NEST_H
