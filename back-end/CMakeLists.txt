cmake_minimum_required(VERSION 3.20.0)

#
#   AuthCat Wrapper
#
add_subdirectory(AuthCat)

#
#   CodeCat
#
project(CodeCat)

add_executable(CodeCat ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_sources(CodeCat PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/FrontEndThread.cpp
    ${PROJECT_SOURCE_DIR}/src/ClientThread.cpp
    ${PROJECT_SOURCE_DIR}/src/AcceptorThread.cpp
)

target_include_directories(CodeCat PUBLIC 
    ${PROJECT_SOURCE_DIR}/AuthCat/include
    ${PROJECT_SOURCE_DIR}/AuthCat/json/single_header
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(CodeCat PUBLIC AuthCat)
