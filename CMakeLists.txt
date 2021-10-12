cmake_minimum_required(VERSION 3.14)
project(Weather)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS system filesystem program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(Weather src/sources/main.cpp src/sources/client.cpp src/sources/network.cpp src/sources/application.cpp)

target_include_directories(Weather PUBLIC src/headers/ )
target_link_libraries(Weather ${Boost_LIBRARIES} pthread) #Boost::filesystem Boost::system
