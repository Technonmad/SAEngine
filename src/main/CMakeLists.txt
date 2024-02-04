cmake_minimum_required(VERSION 3.15.0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(SAEngine_SRC
    MainWindow.ui
    MainWindow.cpp
    MainWindow.h
    main.cpp
)

add_executable(SAEngine ${SAEngine_SRC})

target_include_directories(SAEngine PUBLIC
    ../libs/ModelWindow
    ../libs/ToolsIcon
    ../libs/ModellingTools/ManufactureEntities/Warehouse
)

# Use the Widgets module from Qt 5
target_link_libraries(
    SAEngine
    Qt6::Widgets
    ModelWindowLib
    ToolsIconLib
    WarehouseLib
)

