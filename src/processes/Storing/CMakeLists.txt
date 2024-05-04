cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(WarehouseSrc
	  WarehouseItem.h
		WarehouseItem.cpp
)

add_library(Warehouse STATIC ${WarehouseSrc})

target_include_directories(Warehouse PUBLIC
    ../
)

target_link_libraries(
	  Warehouse PRIVATE
		GraphicsItem
)
