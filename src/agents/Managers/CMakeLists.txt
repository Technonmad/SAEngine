cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(ManagersSrc
	  Managers.h
	  Managers.cpp
)

add_library(Managers STATIC ${ManagersSrc})

target_include_directories(Managers PUBLIC
    ../
)

target_link_libraries(
	  Managers PRIVATE
		GraphicsItem
)
