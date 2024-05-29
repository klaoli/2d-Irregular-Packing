#include <iostream>
#include "parameters.h"
#include "dataloader.h"


using namespace MyNest;

// 在类外部定义并初始化静态成员变量
std::string Parameters::piecePath;
std::string Parameters::nfpPath;
std::string Parameters::ifrPath;
std::string Parameters::resultPath;
double Parameters::maxRunTime;
size_t Parameters::orientations;


int main() {
    MyNest::Parameters::piecePath = "dataset/jakobs1.txt";
    DataLoader *dataloader = DataLoader::getInstance();
    dataloader->dataLoadFromTxt();



    return 0;
}










