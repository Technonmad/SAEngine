cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(ArrowSrc
    Arrow.h
    Arrow.cpp
)

add_library(Arrow STATIC ${ArrowSrc})

target_include_directories(Arrow PUBLIC
    ../
)

target_link_libraries(
    Arrow PRIVATE
    Item
)
