cmake_minimum_required(VERSION 3.17)
project(philo_three C)

set(CMAKE_C_STANDARD 99)

add_executable(philo_three main.c philo.h init.c error_handler.c sem_utils.c actions.c utils.c)