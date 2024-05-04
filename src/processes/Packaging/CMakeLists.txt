cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(PackagingSrc
	  Packaging.h
	  Packaging.cpp
)

add_library(Packaging STATIC ${PackagingSrc})

target_include_directories(Packaging PUBLIC
    ../
)

target_link_libraries(
	  Packaging PRIVATE
		GraphicsItem
)
