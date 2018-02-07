cmake_minimum_required(VERSION 2.8)
project(bench)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        common.h
        read_custom.c
        read_custom.h
        getcustom.c
        getcustom.h
        socket.c
        socket.h
        main.c)

add_executable(bench ${SOURCE_FILES})
