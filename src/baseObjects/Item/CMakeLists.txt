cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(GraphicsItemSrc
	  GraphicsItem.h
		GraphicsItem.cpp
		GraphicsItemFactory.cpp
		GraphicsItemFactory.h
		IGraphicsItemFactory.h
)

add_library(GraphicsItem STATIC ${GraphicsItemSrc})

target_include_directories(GraphicsItem PUBLIC
    ../
)

target_link_libraries(
	  GraphicsItem PRIVATE
		Arrow
		Warehouse
)
