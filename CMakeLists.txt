cmake_minimum_required(VERSION 3.10.0)
project(SDR_convert_to_HDR VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags to make the AVX on
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mavx -mavx2 -mfma -ffast-math -O2")

# I add the source project folder (CMAKE_SOURCE_DIR) for compiler to look for header files in it (like avx_mathfun.h)
include_directories(${CMAKE_SOURCE_DIR})

#  Dir to opencv
set(OpenCV_DIR "C:/opencv-4.10.0/opencvbuild")

# Find Open CV package
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable and link libraries
add_executable(SDR_convert_to_HDR main.cpp)
target_link_libraries(SDR_convert_to_HDR ${OpenCV_LIBS})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
