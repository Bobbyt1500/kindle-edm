cmake_minimum_required(VERSION 3.16)

project(KindleEDM)

# Use c++20
set(CMAKE_CXX_STANDARD 20)

# Dont build raylib examples
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Set directory for executible to be placed
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release)

# Copy resources to the release dir
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR}/release)

add_subdirectory(raylib)

add_executable(KindleEDM main.cpp graphics.cpp data.cpp)

if(MINGW)
  target_link_libraries(KindleEDM ws2_32)
endif()

target_link_libraries(KindleEDM raylib)