cmake_minimum_required(VERSION 3.10.0)
project(SDR_convert_to_HDR VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SDR_convert_to_HDR main.cpp)

# Find Open CV package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable and link libraries
add_executable(SDR2HDR main.cpp)
target_link_libraries(SDR2HDR ${OpenCV_LIBS})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
