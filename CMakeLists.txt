cmake_minimum_required(VERSION 3.23)
project(Threads C)

set(CMAKE_C_STANDARD 99)

add_executable(Threads main.c threadProblem.c common.h common_threads.h t1.c 27-1.c counter.c sloppycounter.c CPU.c concurrent_LinkedList.c concurrent_stack.c)
