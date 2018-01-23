cmake_minimum_required(VERSION 3.7)
project(getopt_custom)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        getcustom.c
        getcustom.h
        socket.c
        socket.h
        main.c)

add_executable(getopt_custom ${SOURCE_FILES})