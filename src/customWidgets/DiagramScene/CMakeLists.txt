cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(DiagramSceneSrc
    DiagramScene.h
    DiagramScene.cpp
)

set(CMAKE_AUTOMOC ON)

add_library(DiagramScene STATIC ${DiagramSceneSrc})

target_include_directories(DiagramScene PUBLIC
    ../
)

target_link_libraries(
    DiagramScene PRIVATE
		Qt6::Widgets
		Item
		Arrow
)
