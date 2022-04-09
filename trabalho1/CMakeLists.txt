cmake_minimum_required(VERSION 3.15)
project(trabalho1 C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra)
add_executable(trabalho1 main.c Funcoes.c Funcoes.h)