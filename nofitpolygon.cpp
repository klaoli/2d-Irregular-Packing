#include "nofitpolygon.h"
#include "libnfporb-master/src/libnfporb.hpp"
using namespace MyNest;


NFP* NFP::nfp = nullptr;

NFP::NFP() {

}

NFP* NFP::getInstance() {
    if (nfp == nullptr) {
        nfp = new NFP;
    }
    return nfp;
}

polygon_t NFP::generateNfp(libnfporb::polygon_t &polyA, libnfporb::polygon_t &polyB) const {

    libnfporb::nfp_t nfp = libnfporb::generate_nfp(polyA, polyB);

    static GeometryConvert *converter = GeometryConvert::getInstance();

    return converter->libNfp2BoostPolygon(nfp);

}

polygon_t NFP::generateIfr(const box_t &bin, const polygon_t &poly) const {
    box_t envelope;
    bg::envelope(poly, envelope);
    auto & refer_point = poly.outer().front();
    polygon_t ifr;
    bg::append(ifr.outer(), point_t(bin.min_corner().x() - envelope.min_corner().x() + refer_point.x(),
        bin.min_corner().y() - envelope.min_corner().y() + refer_point.y()));
    bg::append(ifr.outer(), point_t(bin.max_corner().x() - envelope.max_corner().x() + refer_point.x(),
        bin.min_corner().y() - envelope.min_corner().y() + refer_point.y()));
    bg::append(ifr.outer(), point_t(bin.max_corner().x() - envelope.max_corner().x() + refer_point.x(),
        bin.max_corner().y() - envelope.max_corner().y() + refer_point.y()));
    bg::append(ifr.outer(), point_t(bin.min_corner().x() - envelope.min_corner().x() + refer_point.x(),
        bin.max_corner().y() - envelope.max_corner().y() + refer_point.y()));
    bg::append(ifr.outer(), point_t(bin.min_corner().x() - envelope.min_corner().x() + refer_point.x(),
        bin.min_corner().y() - envelope.min_corner().y() + refer_point.y()));
    bg::correct(ifr);
    return ifr;
}

//polygon_t NFP::generateNfp(Piece &pA, Piece &pB) const {

//}

polygon_t NFP::generateIfr(const box_t &bin, const Piece &piece) const {
    box_t envelope = piece.getEnvelope();
    auto & refer_point = piece.polygon.outer().front();
    polygon_t ifr;
    bg::append(ifr.outer(), point_t(bin.min_corner().x() - envelope.min_corner().x() + refer_point.x(),
        bin.min_corner().y() - envelope.min_corner().y() + refer_point.y()));
    bg::append(ifr.outer(), point_t(bin.max_corner().x() - envelope.max_corner().x() + refer_point.x(),
        bin.min_corner().y() - envelope.min_corner().y() + refer_point.y()));
    bg::append(ifr.outer(), point_t(bin.max_corner().x() - envelope.max_corner().x() + refer_point.x(),
        bin.max_corner().y() - envelope.max_corner().y() + refer_point.y()));
    bg::append(ifr.outer(), point_t(bin.min_corner().x() - envelope.min_corner().x() + refer_point.x(),
        bin.max_corner().y() - envelope.max_corner().y() + refer_point.y()));
    bg::append(ifr.outer(), point_t(bin.min_corner().x() - envelope.min_corner().x() + refer_point.x(),
        bin.min_corner().y() - envelope.min_corner().y() + refer_point.y()));
    bg::correct(ifr);
    return ifr;
}


