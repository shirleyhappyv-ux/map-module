#include "../include/MapSearch.h" // 确保引用正确
#include <vector>                 // 编译器提示你需要这个
#include <iostream>

// 构造函数实现
MapSearch::MapSearch(const std::string& gpkgPath) {
    GDALAllRegister();
    poDS = (GDALDataset*)GDALOpenEx(gpkgPath.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (!poDS) {
        throw std::runtime_error("无法打开 GPKG 文件");
    }
}

// 析构函数实现
MapSearch::~MapSearch() {
    if (poDS) GDALClose(poDS);
}

// 搜索函数实现
std::vector<SearchResult> MapSearch::searchByName(const std::string& nameKeyword) {
    std::vector<SearchResult> results;
    
    // 使用双引号包裹图层名，确保兼容性；使用 LIKE 模糊匹配
    std::string sql = "SELECT name, ST_Y(geom), ST_X(geom) FROM 'gis_osm_places_free' WHERE name LIKE '%" + nameKeyword + "%'";
    
    OGRLayer* poLayer = poDS->ExecuteSQL(sql.c_str(), NULL, NULL);
    if (poLayer) {
        for (auto& poFeature : poLayer) {
            SearchResult res;
            // 获取名称，如果为空则设为“未知”
            res.name = poFeature->GetFieldAsString("name");
            res.lat = poFeature->GetFieldAsDouble(1); // 对应 ST_Y(geom)
            res.lon = poFeature->GetFieldAsDouble(2); // 对应 ST_X(geom)
            results.push_back(res);
        }
        poDS->ReleaseResultSet(poLayer);
    }
    return results;
}