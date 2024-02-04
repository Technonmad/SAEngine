cmake_minimum_required(VERSION 3.5)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(Warehouse
    Warehouse.cpp
    Warehouse.h
)

add_library(WarehouseLib STATIC ${Warehouse})
