cmake_minimum_required(VERSION 3.28)
project(koronome)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
find_package(libzip REQUIRED)

add_custom_target(
    pk3 ALL
    COMMAND zip -9 -r "${CMAKE_BINARY_DIR}/koronome.pk3" .
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/pk3"
)

add_subdirectory(src)
