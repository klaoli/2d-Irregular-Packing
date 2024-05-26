#ifndef READPOLYGONFILE_H
#define READPOLYGONFILE_H

#include "piece.h"
#include "geometry.h"

#include <vector>

namespace MyNest {

class DataLoader{
public:

    static DataLoader* dataLoader;
    static DataLoader* getInstance();

    void dataLoadNFPs();
    void dataLoadIFPs();
    void dataLoadFromTxt();
    void dataLoadFromTxt2();
    void dataLoadFromSql();

    box_t bin;
    std::vector<Piece> pieces;

private:
    DataLoader();
    DataLoader(const DataLoader&) = delete;
    void operator=(const DataLoader&) = delete;

};

}


#endif // READPOLYGONFILE_H
