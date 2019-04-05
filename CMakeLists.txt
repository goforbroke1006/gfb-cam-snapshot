cmake_minimum_required(VERSION 3.0)
project(gfb-cam-snapshot)

set(CMAKE_CXX_STANDARD 14)

add_executable(gfb-cam-snapshot main.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(gfb-cam-snapshot ${OpenCV_LIBS})

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS system filesystem)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(gfb-cam-snapshot ${Boost_LIBRARIES})
endif ()
