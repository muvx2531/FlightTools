cmake_minimum_required(VERSION 3.16)

project(Flight VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Widgets Gui Qml Quick Charts QuickControls2 REQUIRED)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appFlight
    main.cpp
)

qt_add_qml_module(appFlight
    URI Flight
    VERSION 1.0
    QML_FILES
        Main.qml
        RealtimeOscilloscope.qml
        PIDadjustmentPanel.qml
        Joystick.qml
        ProtocolConsole.qml
        Plot3DOrientation.qml
        FlightInstument.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFlight PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFlight
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appFlight
    PRIVATE 
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Charts
    Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appFlight
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
