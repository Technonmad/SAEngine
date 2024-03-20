cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(EdgeSrc
    Edge.h
    Edge.cpp
)

add_library(Edge STATIC ${EdgeSrc})

target_include_directories(Edge PUBLIC
    ../
)

target_link_libraries(
    Edge PRIVATE
    ManagerAgent
#    GraphWidget
)
