cmake_minimum_required(VERSION 3.12)

project(Rithmatist)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS "sdl-config --cflags --libs")
set(CMAKE_CXX_FLAGS "-lpthread -lm")

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
    ${CMAKE_SOURCE_DIR}/src/Debug.hpp
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
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
