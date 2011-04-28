project(Grooveshark)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(Grooveshark_SRCS Grooveshark.cpp main.cpp)
qt4_automoc(${Grooveshark_SRCS})
add_executable(Grooveshark ${Grooveshark_SRCS})
target_link_libraries(Grooveshark ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
