cmake_minimum_required(VERSION 3.5.0)

find_package(Qt6Widgets)
include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)

set(SecuritySrc
	  Security.h
	  Security.cpp
)

add_library(Security STATIC ${SecuritySrc})

target_include_directories(Security PUBLIC
    ../
)

target_link_libraries(
	  Security PRIVATE
		GraphicsItem
)
