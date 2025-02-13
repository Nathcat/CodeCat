cmake_minimum_required(VERSION 3.30.0)

project(CodeCat)

add_executable(CodeCat src/main.cpp)

target_include_directories(CodeCat PUBLIC ./include)