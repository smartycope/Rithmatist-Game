cmake_minimum_required(VERSION 3.12)

project(test)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
#set(CMAKE_CXX_FLAGS "-lpthread -lm")
set(CMAKE_CXX_FLAGS "-pthread")

# set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)

# put the binaries where I want them
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#set(CMAKE_DEBUG_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug)

# stuff for debugging
#set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
#set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# To make everything fully multithreaded compliant
set(CMAKE_THREAD_LIBS_INIT "-lpthread")
#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# gcc -o test test.c sdl-config --cflags --libs

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(SRC_LIST
    ${CMAKE_SOURCE_DIR}/Arena.cpp
    ${CMAKE_SOURCE_DIR}/Gui.cpp
    ${CMAKE_SOURCE_DIR}/Line.cpp
    ${CMAKE_SOURCE_DIR}/LineForbiddence.cpp
    ${CMAKE_SOURCE_DIR}/LineMaking.cpp
    ${CMAKE_SOURCE_DIR}/LineVigor.cpp
    ${CMAKE_SOURCE_DIR}/LineWarding.cpp
    ${CMAKE_SOURCE_DIR}/Globals.cpp
    ${CMAKE_SOURCE_DIR}/Point.cpp
    ${CMAKE_SOURCE_DIR}/Color.cpp
    ${CMAKE_SOURCE_DIR}/Player.cpp
    ${CMAKE_SOURCE_DIR}/main.cpp
)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

# set(BINARY_NAME "${PROJECT_NAME}-${CMAKE_BUILD_TYPE}")

add_executable(${PROJECT_NAME} ${SRC_LIST})

#link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} dl)
#target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})