cmake_minimum_required(VERSION 3.5)
project(raytracing CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)

add_executable(demo main.cpp RayWidget.cpp RayWidget.h default.qss stylesheet.qrc)
target_link_libraries(demo Qt5::Widgets)
