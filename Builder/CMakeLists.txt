cmake_minimum_required(VERSION 3.16)

project(BuildPattern)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(builder
    src/main.cpp
    src/Person.cpp
    src/PersonAddressBuilder.cpp
    src/PersonBuilder.cpp
    src/PersonJobBuilder.cpp
)