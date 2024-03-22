cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(NodeSrc
    Node.h
    Node.cpp
)

add_library(Node STATIC ${NodeSrc})

target_include_directories(Node PUBLIC
    ../
)

target_link_libraries(
    Node PRIVATE
    Edge
    GraphWidget
)
