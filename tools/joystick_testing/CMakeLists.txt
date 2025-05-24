cmake_minimum_required(VERSION 3.22)
project(joystick_testing)

set(CMAKE_CXX_STANDARD 20)

add_executable(joystick_testing main.c)
set(SDL_SHARED  ON)
set(SDL_UNIX_CONSOLE_BUILD ON)

include(FetchContent)
#find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared )
FetchContent_Declare(SDL3 URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.0.tar.gz)
FetchContent_MakeAvailable(SDL3)
#cmake_print_variables(${LIBWEBSOCKETS_INCLUDE_DIRS})

target_include_directories(
        joystick_testing
        PRIVATE
#        /usr/local/include/SDL3
)

target_link_libraries(
        joystick_testing
        PRIVATE
        SDL3::SDL3
)


