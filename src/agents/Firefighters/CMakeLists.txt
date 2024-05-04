cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(FirefightersSrc
	  Firefighters.h
	  Firefighters.cpp
)

add_library(Firefighters STATIC ${FirefightersSrc})

target_include_directories(Firefighters PUBLIC
    ../
)

target_link_libraries(
	  Firefighters PRIVATE
		GraphicsItem
)
