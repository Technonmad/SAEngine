cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(ItemSrc
	  Item.h
		Item.cpp
)

add_library(Item STATIC ${ItemSrc})

target_include_directories(Item PUBLIC
    ../
)

target_link_libraries(
	  Item PRIVATE
    Edge
    GraphWidget
)
