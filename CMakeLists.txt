cmake_minimum_required(VERSION 4.1.2)

project(antfarm)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(antfarm)

target_sources(
    antfarm
    PRIVATE
        src/main.cpp
        src/ant.cpp
        src/grid.cpp
        src/tiling.cpp
        src/afmainwindow.cpp
        src/afview.cpp
        src/afscene.cpp
)

target_include_directories(
    antfarm
    PUBLIC
        include
)

target_include_directories(antfarm PUBLIC include)

target_link_libraries(antfarm PUBLIC Qt6::Widgets)

install(TARGETS antfarm)
