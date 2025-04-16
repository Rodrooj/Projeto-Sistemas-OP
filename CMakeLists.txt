cmake_minimum_required(VERSION 3.30)
project(Projeto-Sistemas_OP C)

set(CMAKE_C_STANDARD 11)

include_directories("teste jetbrains")

add_executable(Projeto-Sistemas_OP
        main.c
        item.c
        item.h)
