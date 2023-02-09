cmake_minimum_required(VERSION 3.10.2)
project(bomberman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/libs/linux/")
set(CMAKE_SUPPRESS_REGENERATION true)

link_directories(${CMAKE_SOURCE_DIR}/libs/linux)

if (WIN32)
	link_directories(${CMAKE_SOURCE_DIR})
ENDIF()

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp)

file(GLOB_RECURSE HEADER_FILES 
    ${CMAKE_SOURCE_DIR}/include/Component/*.hpp
	${CMAKE_SOURCE_DIR}/include/Entity/*.hpp
	${CMAKE_SOURCE_DIR}/include/Interface/*.hpp
	${CMAKE_SOURCE_DIR}/include/Storage/*.hpp
	${CMAKE_SOURCE_DIR}/include/System/*.hpp)

include_directories(
	${CMAKE_SOURCE_DIR}/include/Component
	${CMAKE_SOURCE_DIR}/include/Entity
	${CMAKE_SOURCE_DIR}/include/Interface
	${CMAKE_SOURCE_DIR}/include/Storage
	${CMAKE_SOURCE_DIR}/include/System
	${CMAKE_SOURCE_DIR}/libs/include)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})


if (WIN32)

find_package(IRRLICHT REQUIRED)
set(LIBS opengl32 IRRLICHT)

ELSE()

find_library(IRRLICHT_LIBRARIES irrlicht)
set(IRRLICHT_LIBRARY    -I/usr/X11R6/include
                            -ffast-math
                            -I./libs/include/
                            -L./libs/Linux/
                            -lIrrlicht
                            -lGL
                            -lGLU
                            -lXext
                            -lX11
                            -lXxf86vm
                            -lsfml-graphics
                            -lsfml-window
                            -lsfml-system
                            sfml-audio)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g3")

ENDIF()

target_link_libraries(${PROJECT_NAME} ${IRRLICHT_LIBRARY})
