#ifndef NFP_H
#define NFP_H
#include "piece.h"

namespace MyNest {

    class NFP
    {
    public:
        Piece pA, pB;
        static NFP& getInstance();



    private:
        NFP();
        NFP(const NFP&) = delete;
        void operator=(const NFP&) = delete;
    };

}


#endif // NFP_H
