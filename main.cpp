#include <iostream>
#include "include/MapSearch.h"

int main() {
    try {
        std::string gpkgPath = "../data/map_data.gpkg";
        std::cout << "正在初始化地图搜索模块，读取文件: " << gpkgPath << std::endl;
        
        MapSearch searcher(gpkgPath);
        std::cout << "初始化成功，开始搜索..." << std::endl;
        
        auto results = searcher.searchByName("重庆");
        
        std::cout << "搜索完成，共找到 " << results.size() << " 条结果。" << std::endl;
        
        for (const auto& res : results) {
            std::cout << "找到: " << res.name << " | 坐标: " << res.lat << "," << res.lon << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "运行出错: " << e.what() << std::endl;
    }
    return 0;
}