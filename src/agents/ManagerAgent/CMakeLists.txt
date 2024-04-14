cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(ManagerAgentSrc
    ManagerAgent.h
    ManagerAgent.cpp
)

add_library(ManagerAgent STATIC ${ManagerAgentSrc})

target_include_directories(ManagerAgent PUBLIC
    ../
)

target_link_libraries(
    ManagerAgent PRIVATE
    Edge
    GraphWidget
)
