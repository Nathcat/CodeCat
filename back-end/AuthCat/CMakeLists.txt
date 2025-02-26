cmake_minimum_required(VERSION 3.20.0)

#
#   AuthCat
#
project(AuthCat)

add_library(AuthCat STATIC ${PROJECT_SOURCE_DIR}/src/AuthCat.cpp)

target_include_directories(AuthCat PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/cpp-httplib/benchmark/cpp-httplib-base
)

target_link_libraries(AuthCat PUBLIC 
    ssl
    crypto
)

#
#   HTTPLibTest
#
project(HTTPLibTest)

add_executable(HTTPLibTest ${PROJECT_SOURCE_DIR}/tests/HTTPLibTest.cpp)

target_include_directories(HTTPLibTest PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/cpp-httplib/benchmark/cpp-httplib-base
)

target_link_libraries(HTTPLibTest PUBLIC 
    ssl
    crypto
)
