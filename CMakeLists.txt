cmake_minimum_required(VERSION 3.0)
project(storage-service)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags for both Debug and Release configurations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g -DDEBUG=2")

include_directories(include)

file(GLOB SOURCES "queryProcessing/*.cc" "connect/*.cc")

# Add the executable for the server
add_executable(server server.cc ${SOURCES})

# Add the executable for the client
add_executable(client client.cc ${SOURCES})
