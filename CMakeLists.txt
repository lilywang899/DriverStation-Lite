cmake_minimum_required(VERSION 3.12.0)
project(console_ds)
find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs -Werror -fPIC -g -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread  -Wno-unused-local-typedefs  -fPIC -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs  -fPIC -g -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
#set(SDL3_DIR "/usr/local/include/SDL3")

find_package(spdlog REQUIRED)
find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared )

add_executable(
        console_ds
        src/main.c
        src/interface.c
        src/joystick.c
)
#cmake_print_variables(${LIBWEBSOCKETS_INCLUDE_DIRS})

target_include_directories(
        console_ds
        PRIVATE
        include
        lib/include
        /usr/local/include/SDL3
)

target_link_libraries(
       console_ds
       PRIVATE
       ds
       ncurses
       SDL3::SDL3
)

add_subdirectory(lib)
#target_compile_options(mqtt PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-function)
target_compile_options(console_ds PRIVATE -Wall -Wextra -Wno-unused-function)

