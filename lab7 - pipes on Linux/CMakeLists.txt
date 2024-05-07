cmake_minimum_required(VERSION 3.28)
project(lab7___pipes_on_Linux C)

set(CMAKE_C_STANDARD 11)

add_executable(lab7___pipes_on_Linux main.c
        fifo.c
        fifo1.c
        semaphore_with_pipe.c)
