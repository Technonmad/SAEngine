cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(TecnicianSrc
	  Tecnician.h
	  Tecnician.cpp
)

add_library(Tecnician STATIC ${TecnicianSrc})

target_include_directories(Tecnician PUBLIC
    ../
)

target_link_libraries(
	  Tecnician PRIVATE
		GraphicsItem
)
