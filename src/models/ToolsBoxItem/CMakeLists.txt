cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(ToolsBoxItemSrc
    ToolsBoxItem.h
    ToolsBoxItem.cpp
)

add_library(ToolsBoxItem STATIC ${ToolsBoxItemSrc})
