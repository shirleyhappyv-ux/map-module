#ifndef MAPSEARCH_H
#define MAPSEARCH_H

#include <string>
#include <vector>
#include <gdal_priv.h>
#include <ogrsf_frmts.h>

struct SearchResult {
    std::string name;
    double lat;
    double lon;
};

class MapSearch {
public:
    MapSearch(const std::string& gpkgPath); // 只有声明
    ~MapSearch();                           // 只有声明
    std::vector<SearchResult> searchByName(const std::string& nameKeyword);
private:
    GDALDataset* poDS;
};

#endif