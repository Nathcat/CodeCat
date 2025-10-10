cmake_minimum_required(VERSION 3.26.0)

project(CodeCat)

set(DEBUG_RELEASE_PATH ${CMAKE_SOURCE_DIR}/build/Debug)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)
link_directories(${GTK4_LIBRARY_DIRS})
add_compile_options(${GTK4_CFLAGS_OTHER})
set(LIBRARIES ${LIBRARIES} ${GTK4_LIBRARIES})

include_directories(${GTK4_INCLUDE_DIRS})

add_executable(CodeCat src/main.c)
target_link_libraries(CodeCat PUBLIC ${LIBRARIES})

message(STATUS "Libraries: ${LIBRARIES}")
message(STATUS "Lib dirs: ${GTK4_LIBRARY_DIRS}")
message(STATUS "Include dirs: ${GTK4_INCLUDE_DIRS}") 
message(STATUS "Debug install dir: ${DEBUG_RELEASE_PATH}")
message(STATUS "Flags: ${GTK4_CFLAGS_OTHER}")
message(STATUS "Cmake system lib path: ${CMAKE_SYSTEM_LIBRARY_PATH}")


install(TARGETS CodeCat
    RUNTIME_DEPENDENCIES
        DIRECTORIES ${GTK4_LIBRARY_DIRS} ${CMAKE_SYSTEM_LIBRARY_PATH}
        PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
        POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
    CONFIGURATIONS Debug 
    DESTINATION ${DEBUG_RELEASE_PATH}
)

