cmake_minimum_required(VERSION 3.14)

project(2dIrregularPacking LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 定义 Boost 根目录和库目录变量
set(BOOST_ROOT "D:/C++Library/boost_1_65_0")
set(BOOST_LIBRARY_DIR "${BOOST_ROOT}/libs")

# 使用 find_package 查找 Qt 和设置 Qt 组件
# find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
# find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

# 设置 Boost 和项目特定的包含目录
include_directories(${BOOST_ROOT})
include_directories(${CMAKE_SOURCE_DIR}/include)
#include_directories(${CMAKE_SOURCE_DIR}/libnfporb-master/src)
#include_directories(${CMAKE_SOURCE_DIR}/libnfporb-master/src/algo)


# 查找 include 和 src 目录下的所有文件
file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/libnfporb-master/src/*.hpp
    ${CMAKE_SOURCE_DIR}/libnfporb-master/src/algo/*.hpp
)

# 打印找到的文件（可选，用于调试）
# message("Header files: ${HEADER_FILES}")

# 指定源文件和头文件
set(HEADERS
    geometry.h
    piece.h
    vector.h
    dataloader.h
    parameters.h
    nofitpolygon.h
    datawrite.h
    packing.h
#    plot.h
)


set(SRCS
    main.cpp
    geometry.cpp
    piece.cpp
    vector.cpp
    dataloader.cpp
    nofitpolygon.cpp
    datawrite.cpp
    packing.cpp
#    plot.cpp
)

# 添加可执行文件
add_executable(2dIrregularPacking ${SRCS} ${HEADERS} ${HEADER_FILES})

# 针对目标设置链接库路径
target_link_directories(2dIrregularPacking PRIVATE
    ${BOOST_LIBRARY_DIR}
    ${CMAKE_SOURCE_DIR}/lib
)

# 链接库
target_link_libraries(2dIrregularPacking
    # Qt${QT_VERSION_MAJOR}::Core
    clipper
)
