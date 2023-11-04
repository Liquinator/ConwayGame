cmake_minimum_required(VERSION 3.27.7)

project(CONWAY)
set(CMAKE_CXX_STANDARD 17)

set(SDL2_DIR "/opt/homebrew/Cellar/sdl2/2.28.4/lib/cmake/SDL2")
find_package(SDL2 REQUIRED)

file(GLOB SRC_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/main.cpp" ${SRC_FILES})
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
if (APPLE)
    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
endif()