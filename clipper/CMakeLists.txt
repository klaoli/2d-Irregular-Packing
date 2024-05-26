cmake_minimum_required(VERSION 3.14)

project(ClipperLibrary LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 包含头文件目录
include_directories(include)

# 定义源文件
set(SOURCES
    src/clipper.cpp
)

# 创建静态库
add_library(clipper_static STATIC ${SOURCES})
set_target_properties(clipper_static PROPERTIES OUTPUT_NAME "clipper")

# 安装目标
install(TARGETS clipper_static
    ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/../lib
)

# 安装头文件
# install(DIRECTORY include/ DESTINATION ${CMAKE_SOURCE_DIR}/../include)
