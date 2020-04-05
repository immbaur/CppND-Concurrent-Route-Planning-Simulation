cmake_minimum_required(VERSION 3.7)


project(Concurrent_Route_Planning_Simulation)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
# set(CXX_FLAGS "-Wall")
# set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

# add_definitions(-std=c++17)

find_package(OpenCV 4.1 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIBRARY_DIRS})
add_definitions(${OpenCV_DEFINITIONS})

# Find all executables
file(GLOB project_SRCS src/*.cpp) #src/*.h

add_executable(Concurrent_Route_Planning_Simulation ${project_SRCS})
target_link_libraries(Concurrent_Route_Planning_Simulation ${OpenCV_LIBRARIES})
