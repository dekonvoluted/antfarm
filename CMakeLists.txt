cmake_minimum_required( VERSION 3.3 )

project( antfarm )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

find_package( Qt5 COMPONENTS Widgets REQUIRED )

set( CMAKE_AUTOMOC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

set( cpp_sources main.cpp afmainwindow.cpp afview.cpp afscene.cpp fpswidget.cpp )

add_executable( antfarm ${cpp_sources} )

target_link_libraries( antfarm Qt5::Widgets )

