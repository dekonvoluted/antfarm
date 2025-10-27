cmake_minimum_required(VERSION 4.1.2)

project(antfarm)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(antfarm)
target_include_directories(
    antfarm
    PUBLIC
        include
)
target_sources(
    antfarm
    PRIVATE
        src/ant.cpp
        src/grid.cpp
        src/location.cpp
        src/main.cpp
        src/scene.cpp
        src/tiling.cpp
        src/view.cpp
        src/window.cpp
)
target_link_libraries(antfarm PRIVATE Qt6::Widgets)

install(TARGETS antfarm)
