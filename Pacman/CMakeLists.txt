cmake_minimum_required(VERSION 3.10)
project(myproject VERSION 1.0 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(myproject main.cpp)

# specify any libraries the executable depends on
#target_link_libraries(myproject PRIVATE pthread)

# specify where the executable should be installed
#install(TARGETS myproject DESTINATION bin)
