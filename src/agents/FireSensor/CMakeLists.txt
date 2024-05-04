cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(FireSensorSrc
	  FireSensor.h
	  FireSensor.cpp
)

add_library(FireSensor STATIC ${FireSensorSrc})

target_include_directories(FireSensor PUBLIC
    ../
)

target_link_libraries(
	  FireSensor PRIVATE
		GraphicsItem
)
