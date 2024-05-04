cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(ProductionSrc
	  Production.h
	  Production.cpp
)

add_library(Production STATIC ${ProductionSrc})

target_include_directories(Production PUBLIC
    ../
)

target_link_libraries(
	  Production PRIVATE
		GraphicsItem
)
