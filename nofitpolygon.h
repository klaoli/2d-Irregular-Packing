#ifndef NOFITPOLYGON_H
#define NOFITPOLYGON_H

#include "piece.h"

namespace MyNest {

class NFP
{
public:
    static NFP* nfp;
    static NFP* getInstance();

    polygon_t minkowskiDif(const polygon_t &pA, const polygon_t &pB) const;
    polygon_t generateNfp(libnfporb::polygon_t &polyA, libnfporb::polygon_t &polyB) const;
    polygon_t generateIfr(const box_t &bin, const polygon_t &poly) const;

private:
    NFP();
    NFP(const NFP&) = delete;
    void operator=(const NFP&) = delete;
};

}


#endif // NOFITPOLYGON_H
