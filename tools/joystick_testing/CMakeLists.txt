cmake_minimum_required(VERSION 3.22)
project(joystick_testing)

set(CMAKE_CXX_STANDARD 20)

add_executable(joystick_testing main.c)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared )

#cmake_print_variables(${LIBWEBSOCKETS_INCLUDE_DIRS})

target_include_directories(
        joystick_testing
        PRIVATE
        /usr/local/include/SDL3
)

target_link_libraries(
        joystick_testing
        PRIVATE
        SDL3::SDL3
)


