cmake_minimum_required(VERSION 3.16)

# Use c++20
set(CMAKE_CXX_STANDARD 20)

project(KindleEDMPlugin)

# Set XPLM flags
set(CMAKE_CXX_FLAGS  "-DAPL=0 -DIBM=1 -DLIN=0 -DXPLM200=1 -DXPLM210=1 -DXPLM300=1 -DXPLM301=1")

include_directories("SDK/CHeaders/Widgets")
include_directories("SDK/CHeaders/Wrappers")
include_directories("SDK/CHeaders/XPLM")

add_library(KindleEDM SHARED main.cpp)
target_link_libraries(KindleEDM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SDK/Libraries/Win/XPLM_64.lib)
target_link_libraries(KindleEDM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/SDK/Libraries/Win/XPWidgets_64.lib)
