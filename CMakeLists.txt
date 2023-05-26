cmake_minimum_required(VERSION 3.26.3)

project(state_machine)
include_directories(include)

set(LIB_SOURCES "source/lib/stateMachine.c" "source/lib/stateMachine_debug.c")

set(MAIN_SOURCE "source/main.c")

set(SOURCES ${LIB_SOURCES} ${MAIN_SOURCE})

add_executable(${PROJECT_NAME} ${SOURCES})