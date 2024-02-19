cmake_minimum_required(VERSION 3.5)

project(SAEngine VERSION 0.1 LANGUAGES CXX)

add_subdirectory(src/main)
add_subdirectory(src/models)
add_subdirectory(src/ui)

qt_add_resources(SAEngine "tools_images"
        PREFIX "/images/tools"
        FILES images/tools/arm.png
)

qt_add_resources(SAEngine "agents_images"
        PREFIX "/images/agents"
        FILES images/agents/arm.png
)
