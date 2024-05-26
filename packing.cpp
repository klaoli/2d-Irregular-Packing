#include "packing.h"

using namespace MyNest;
Packing* Packing::packing = nullptr;

box_t Packing::bin;
std::vector<Piece> Packing::pieces;
std::vector<std::vector<Piece>> Packing::piecesCache;
std::unordered_map<std::string, polygon_t> Packing::nfpsCache;


Packing::Packing() {

}


Packing* Packing::getInstance() {
    if (packing == nullptr) {
        packing = new Packing;
    }
    return packing;
}

std::string Packing::getNfpKey(const Piece &A,const Piece &B) {
    return std::to_string(A.id) + std::to_string(A.rotation) +
            std::to_string(B.id) + std::to_string(B.rotation);
}

std::string Packing::getIfrKey(const Piece &A) {
    return std::to_string(A.id) + std::to_string(A.rotation);
}


void Packing::preprocess() {
    // 放缩  简化  平移到原点


}


void Packing::getNfps() {


}


void Packing::getIfrs() {


}


void Packing::run() {


}
