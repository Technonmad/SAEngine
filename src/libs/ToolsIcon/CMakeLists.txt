cmake_minimum_required(VERSION 3.5)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(ToolsIcon
    ToolsIcon.cpp
    ToolsIcon.h
)

add_library(ToolsIconLib STATIC ${ToolsIcon})
