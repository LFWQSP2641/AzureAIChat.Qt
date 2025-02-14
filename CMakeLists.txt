cmake_minimum_required(VERSION 3.16)

project(AzureAIChat VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Network QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_policy(
    SET QTP0004 NEW
)

set(SOURCES
    src/main.cpp
    src/Settings.cpp
    src/APIConfig.cpp
    src/utils/Global.cpp
    src/Network/AzureAPIManager.cpp
    src/MessagesList.cpp
)

set(HEADERS
    src/Settings.h
    src/APIConfig.h
    src/utils/Global.h
    src/Network/AzureAPIManager.h
    src/MessagesList.h
)

include_directories(src)
include_directories(${CMAKE_SOURCE_DIR})

qt_add_executable(appAzureAIChat
    ${SOURCES} ${HEADERS}
)

qt_add_qml_module(appAzureAIChat
    URI com.LFWQSP2641.AzureAIChat
    VERSION 1.0
    QML_FILES
        page/Main.qml
    SOURCES
        ${SOURCES} ${HEADERS}
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAzureAIChat PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAzureAIChat
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAzureAIChat
    PRIVATE
        Qt6::Quick
        Qt6::Network
        Qt6::QuickControls2
)

include(GNUInstallDirs)
install(TARGETS appAzureAIChat
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
