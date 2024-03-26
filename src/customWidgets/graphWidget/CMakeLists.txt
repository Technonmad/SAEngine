cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(GraphWidgetSrc
    GraphWidget.h
    GraphWidget.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(GraphWidget STATIC ${GraphWidgetSrc})

target_include_directories(GraphWidget PUBLIC
    ../
)

target_link_libraries(
    GraphWidget PRIVATE
		Qt6::Widgets
    Node
    Edge
)
