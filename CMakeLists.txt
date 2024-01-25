cmake_minimum_required(VERSION 3.5)

project(SAEngine VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_subdirectory(images/tools/)
add_subdirectory(src/main)
add_subdirectory(src/ui)
add_subdirectory(entities/tools/)
add_subdirectory(entities/agents/)

qt_add_resources(SAEngine "tools_images"
        PREFIX "/"
        FILES images/tools/arm.png
)
