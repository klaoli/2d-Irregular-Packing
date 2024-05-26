#ifndef NEST_H
#define NEST_H
#include "piece.h"
#include <vector>
namespace MyNest{
    class Nest
    {
    public:
        static Nest* nest;
        static Nest* getInstance();

        box_t bin;
        std::vector<Piece> pieces;


    private:
        Nest();
        Nest(const Nest&) = delete;
        void operator=(const Nest&) = delete;
    };
}


#endif // NEST_H
