cmake_minimum_required(VERSION 3.20.0)

project(AuthCat)

add_library(AuthCat STATIC ${PROJECT_SOURCE_DIR}/src/AuthCat.cpp)

target_include_directories(AuthCat PUBLIC ${PROJECT_SOURCE_DIR}/include)