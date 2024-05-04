cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(CamSrc
	  Cam.h
	  Cam.cpp
)

add_library(Cam STATIC ${CamSrc})

target_include_directories(Cam PUBLIC
    ../
)

target_link_libraries(
	  Cam PRIVATE
		GraphicsItem
)
