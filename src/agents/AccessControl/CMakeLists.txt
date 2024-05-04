cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(AccessControlSrc
	  AccessControl.h
	  AccessControl.cpp
)

add_library(AccessControl STATIC ${AccessControlSrc})

target_include_directories(AccessControl PUBLIC
    ../
)

target_link_libraries(
	  AccessControl PRIVATE
		GraphicsItem
)
