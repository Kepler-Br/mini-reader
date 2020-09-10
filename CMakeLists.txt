cmake_minimum_required(VERSION 3.17)
project(mini_reader C)

INCLUDE_DIRECTORIES(includes)
INCLUDE_DIRECTORIES(libft)
LINK_DIRECTORIES(libft)
set(CMAKE_C_STANDARD 99)

add_executable(mini_reader src/main.c src/getline.c includes/getline.h)
target_link_libraries(mini_reader ft)