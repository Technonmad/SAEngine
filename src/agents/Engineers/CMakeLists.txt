cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(EngineersSrc
	  Engineers.h
	  Engineers.cpp
)

add_library(Engineers STATIC ${EngineersSrc})

target_include_directories(Engineers PUBLIC
    ../
)

target_link_libraries(
	  Engineers PRIVATE
		GraphicsItem
)
