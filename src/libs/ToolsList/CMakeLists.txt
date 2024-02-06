cmake_minimum_required(VERSION 3.5)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(ToolsList
    ToolsList.cpp
    ToolsList.h
)

add_library(ToolsListLib STATIC ${ToolsList})
