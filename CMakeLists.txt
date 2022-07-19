cmake_minimum_required(VERSION 3.22)
project(mailwriter_qt)

include(FetchContent)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
find_package(nlohmann_json 3.10.5 REQUIRED)
FetchContent_Declare(httplib URL https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.10.9.zip)
FetchContent_MakeAvailable(httplib)

add_executable(mailwriter_qt
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        logindialog.ui
        logindialog.cpp
        logindialog.h
        api.h
        api.cpp)

target_link_libraries(mailwriter_qt
        PUBLIC Qt::Core
        PUBLIC Qt::Gui
        PUBLIC Qt::Widgets
        PRIVATE nlohmann_json::nlohmann_json
        PRIVATE httplib
        )
