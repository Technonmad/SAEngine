cmake_minimum_required(VERSION 3.5)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

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
		Item
		DiagramScene
)

set(saengine_resource_files
	  "../../images/agents/cam.png"
		"../../images/agents/engineers.png"
		"../../images/agents/accessControl.png"
		"../../images/agents/firefighter.png"
		"../../images/agents/fireSensor.png"
		"../../images/agents/security.png"
		"../../images/agents/managers.png"
		"../../images/agents/tecnician.png"
		"../../images/processes/warehouse.png"
		"../../images/processes/production.png"
		"../../images/processes/packaging.png"
		"../../images/processes/delivery.png"
		"../../images/backgrounds/background1.png"
		"../../images/backgrounds/background2.png"
		"../../images/backgrounds/background3.png"
		"../../images/toolbar/pointer.png"
		"../../images/toolbar/linePointer.png"
		"../../images/toolbar/lineColor.png"
		"../../images/toolbar/remove.png"
		"../../images/toolbar/toBack.png"
		"../../images/toolbar/toFront.png"
)

qt_add_resources(SAEngine "SAEngine"
	  PREFIX
		    "/"
		FILES
		    ${saengine_resource_files}
)


