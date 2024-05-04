cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(DeliverySrc
	  Delivery.h
	  Delivery.cpp
)

add_library(Delivery STATIC ${DeliverySrc})

target_include_directories(Delivery PUBLIC
    ../
)

target_link_libraries(
	  Delivery PRIVATE
		GraphicsItem
)
