#ifndef DATALOADER_H
#define DATALOADER_H

#include "piece.h"
#include "geometry.h"

#include <vector>
#include <unordered_map>

namespace MyNest {

class DataLoader{
public:

    static DataLoader* dataLoader;
    static DataLoader* getInstance();

    void dataLoadNfps();
    void dataLoadIfrs();
    void dataLoadFromTxt();
    void dataLoadFromTxt2();
    void dataLoadFromSql();

    static box_t bin;
    static std::vector<Piece> pieces;
    static std::unordered_map<std::string, polygon_t> nfpsCache;
    static std::unordered_map<std::string, polygon_t> ifrsCache;
private:
    DataLoader();
    DataLoader(const DataLoader&) = delete;
    void operator=(const DataLoader&) = delete;

};

}


#endif // DATALOADER_H
