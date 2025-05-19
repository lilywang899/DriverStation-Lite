cmake_minimum_required(VERSION 3.12.0)
find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs -Werror -fPIC -g -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-local-typedefs  -fPIC -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs  -fPIC -g -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

#find_package(SDL3 REQUIRED )
#find_package(spdlog REQUIRED)

set(CFILES
     src/protocols/frc_2015.c 
     src/protocols/frc_2016.c 
     src/protocols/frc_2020.c
     src/config.c 
     src/events.c 
     src/init.c
     src/protocols.c 
     src/socket.c 
     src/utils.c 
     src/timer.c
     src/queue.c
     src/socky.c
)
#cmake_print_variables(${LIBWEBSOCKETS_INCLUDE_DIRS})

set(LIBS
        ${CFILES}
        src/array.c
        src/string.c
        src/joysticks.c
        src/client.c
)

add_library(
         ds
         ${LIBS}
)

target_include_directories(
     ds
     PRIVATE
     include
     PUBLIC
)

target_link_libraries(
       ds
       PRIVATE
        m
        SDL3::SDL3
        spdlog::spdlog
)

target_link_directories(
        ds
        PUBLIC
        /usr/lib/x86_64-linux-gnu
)
#target_compile_options(mqtt PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-function)
#target_compile_options(ds PRIVATE -Wall -Wextra -Wno-unused-function)
target_compile_options(ds PRIVATE  -Wextra -Wno-unused-function)
set_source_files_properties(${CFILES}    PROPERTIES LANGUAGE CXX)
