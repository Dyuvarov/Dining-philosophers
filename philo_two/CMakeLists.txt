cmake_minimum_required(VERSION 3.17)
project(philo_two C)

set(CMAKE_C_STANDARD 99)

add_executable(philo_two main.c init.c philo.h utils.c actions.c error_handler.c sem_utils.c)