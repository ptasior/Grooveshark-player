# set(CMAKE_CXX_COMPILER i586-mingw32msvc-g++)
# set(CMAKE_CC_COMPILER i586-mingw32msvc-gcc)

project(Grooveshark)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)


include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(SRC grooveshark.cpp cookiejar.cpp main.cpp)
set(HDR grooveshark.h cookiejar.h)
set(RES resources.qrc)

QT4_ADD_RESOURCES(RCC ${RES})
QT4_WRAP_CPP(MOCED ${HDR})

add_executable(Grooveshark ${SRC} ${MOCED} ${RCC})
target_link_libraries(Grooveshark ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTWEBKIT_LIBRARY} ${QT_QTNETWORK_LIBRARY})
