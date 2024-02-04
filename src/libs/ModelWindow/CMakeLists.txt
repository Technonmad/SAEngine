cmake_minimum_required(VERSION 3.5)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(ModelWindow
    GV_ModelWindow.cpp
    GV_ModelWindow.h
)

add_library(ModelWindowLib STATIC ${ModelWindow})
