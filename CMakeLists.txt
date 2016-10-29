cmake_minimum_required(VERSION 3.6)
project(algC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

# HASH
set(HASH_FILES hash/hash.c hash/hash.h)
add_library(hash ${HASH_FILES})
add_executable(unit_hash hash/hash_unit.c)
target_link_libraries(unit_hash hash)

set(SOURCE_FILES main.c)
add_executable(algC ${SOURCE_FILES})

