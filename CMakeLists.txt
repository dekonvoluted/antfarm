cmake_minimum_required( VERSION 3.3 )

project( antfarm )

find_package( Qt5 COMPONENTS Widgets REQUIRED )

set( cpp_sources main.cpp )

add_executable( antfarm ${cpp_sources} )

target_link_libraries( antfarm Qt5::Widgets )

