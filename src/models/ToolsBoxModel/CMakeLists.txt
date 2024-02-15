cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(ToolsBoxModelSrc
    ToolsBoxModel.h
    ToolsBoxModel.cpp
)

add_library(ToolsBoxModel STATIC ${ToolsBoxModelSrc})

target_include_directories(ToolsBoxModel PUBLIC
    ../
)
