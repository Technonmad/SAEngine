cmake_minimum_required(VERSION 3.5)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(SAEngine_SRC
    MainWindow.ui
    MainWindow.cpp
    MainWindow.h
    main.cpp
)

qt_add_executable(SAEngine ${SAEngine_SRC})

# Use the Widgets module from Qt 5
target_link_libraries(
    SAEngine PUBLIC
		Qt6::Core
		Qt6::Gui
    Qt6::Widgets
    ToolsBoxModel
		GraphWidget
)
