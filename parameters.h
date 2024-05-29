#ifndef CONFIG_H
#define CONFIG_H
#include <string>

namespace MyNest
{
struct Parameters{
    // double 转 Int, 将坐标变为整数的最小缩放倍数，clipper 函数的调用都需要乘该倍数
    static constexpr int scaleRate = 1000;

    // 曲线宽恕，删除与边距离 curveTolerance 以内的坐标点，如果凸多边形会造成面积减少
    static constexpr double curveTolerance = 0.025;

    // 读取的多边形零件放大倍数
    static constexpr double polygonScaleRate = 100;
    static constexpr double MAXDOUBLE = std::numeric_limits<double>::max();

    double minGap = 0;      // 零件间距，默认为0

    static std::string piecePath;  // 零件数据的路径
    static std::string nfpPath;    // nfp路径
    static std::string ifrPath;    // ifr路径
    static std::string resultPath; // 布局结果存放路径
    static double maxRunTime;      // 算法最大运行时间
    static size_t orientations;
};


}

#endif // CONFIG_H
