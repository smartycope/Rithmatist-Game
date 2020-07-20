cmake_minimum_required(VERSION 3.12)

project(Rithmatist)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER clang)
#set(CMAKE_CXX_FLAGS "-lpthread -lm")
set(CMAKE_CXX_FLAGS "-pthread")

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
    ${CMAKE_SOURCE_DIR}/src/Arena.cpp
    ${CMAKE_SOURCE_DIR}/src/Gui.cpp
    ${CMAKE_SOURCE_DIR}/src/Line.cpp
    ${CMAKE_SOURCE_DIR}/src/LineForbiddence.cpp
    ${CMAKE_SOURCE_DIR}/src/LineMaking.cpp
    ${CMAKE_SOURCE_DIR}/src/LineVigor.cpp
    ${CMAKE_SOURCE_DIR}/src/LineWarding.cpp
    #${CMAKE_SOURCE_DIR}/src/Debug.hpp
    ${CMAKE_SOURCE_DIR}/src/Globals.cpp
    ${CMAKE_SOURCE_DIR}/src/Point.cpp
    ${CMAKE_SOURCE_DIR}/src/Color.cpp
    ${CMAKE_SOURCE_DIR}/src/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

include_directories(
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

#link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} dl)
#target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})


# std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char)@GLIBCXX_3.4 (2)