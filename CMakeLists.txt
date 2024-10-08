cmake_minimum_required(VERSION 3.30)

project(antfarm)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(antfarm)

target_sources(antfarm PRIVATE src/main.cpp)
target_sources(antfarm PRIVATE src/afmainwindow.cpp)
target_sources(antfarm PRIVATE src/afview.cpp)
target_sources(antfarm PRIVATE src/afscene.cpp)

target_include_directories(antfarm PUBLIC include)

target_link_libraries(antfarm Qt6::Widgets)

install(TARGETS antfarm)
