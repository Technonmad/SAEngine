qt_add_executable(SAEngine
    MainWindow.cpp
    MainWindow.h
    MainWindow.ui
    main.cpp
)

target_link_libraries(SAEngine PRIVATE Qt6::Widgets)

set_target_properties(SAEngine PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
