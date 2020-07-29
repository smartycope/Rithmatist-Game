cmake_minimum_required(VERSION 3.12)

project(Rithmatist)

set(CMAKE_CXX_STANDARD 20)


set(SRC_LIST
    # ${CMAKE_SOURCE_DIR}/Line.cpp
    # ${CMAKE_SOURCE_DIR}/Point.cpp
    # ${CMAKE_SOURCE_DIR}/Color.cpp
    ${CMAKE_SOURCE_DIR}/main.cpp
)

add_executable(${PROJECT_NAME} ${SRC_LIST})
