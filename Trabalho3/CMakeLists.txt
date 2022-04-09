cmake_minimum_required(VERSION 3.19)
project(Trabalho3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Trabalho3 main.c Funcoes.c Funcoes.h lib-utf8.h lib-utf8.c cmake-build-debug/param2.txt)
add_compile_options(-Wall -Wextra)