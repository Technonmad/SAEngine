cmake_minimum_required(VERSION 3.5)

project(SAEngine VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_subdirectory(src/main)
add_subdirectory(src/libs)
add_subdirectory(src/ui)

qt_add_resources(SAEngine "tools_images"
        PREFIX "/"
        FILES images/tools/arm.png
)

qt_add_resources(SAEngine "agents_images"
        PREFIX "/"
        FILES images/agents/arm.png
)
