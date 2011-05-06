# set(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
# set(CMAKE_CC_COMPILER i586-mingw32msvc-gcc)

project(Grooveshark)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)


include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(Grooveshark_SRCS Grooveshark.cpp cookiejar.cpp main.cpp)

qt4_add_resources(QtApp_RCC_SRCS resources.qrc)
qt4_automoc(${Grooveshark_SRCS})

add_executable(Grooveshark ${Grooveshark_SRCS} ${QtApp_RCC_SRCS})
target_link_libraries(Grooveshark ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTWEBKIT_LIBRARY} ${QT_QTNETWORK_LIBRARY})
