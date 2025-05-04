cmake_minimum_required(VERSION 3.12.0)
project(console_ds LANGUAGES C CXX)

find_program(CMAKE_C_COMPILER NAMES $ENV{CC} gcc PATHS ENV PATH NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER NAMES $ENV{CXX} g++ PATHS ENV PATH NO_DEFAULT_PATH)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs -Werror -fPIC -g -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread  -Wno-unused-local-typedefs  -fPIC -g -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wno-unused-local-typedefs  -fPIC -g -O0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(SDL_SHARED  ON)
set(SDL_UNIX_CONSOLE_BUILD ON)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(yaml URL https://github.com/jbeder/yaml-cpp/archive/refs/tags/yaml-cpp-0.7.0.tar.gz)
FetchContent_MakeAvailable(yaml)

FetchContent_Declare(spdlog URL https://github.com/gabime/spdlog/archive/refs/tags/v1.14.1.tar.gz)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG        10.2.1  # Use a known stable version
)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(SDL3 URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-3.2.0.tar.gz)
FetchContent_MakeAvailable(SDL3)

#find_package(spdlog REQUIRED)
#find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared )

add_executable(
        console_ds
        src/main.c
        src/interface.c
        src/file_logger.cpp
)
#cmake_print_variables(${LIBWEBSOCKETS_INCLUDE_DIRS})

target_include_directories(
        console_ds
        PRIVATE
        include
        lib/include
        ~/vcpkg/packages/tinyxml2_x64-linux/include
#        /usr/local/include/SDL3
#        /usr/local/include
)

target_link_libraries(
       console_ds
       PRIVATE
       ds
       ncurses
       SDL3::SDL3
        fmt::fmt
       spdlog::spdlog
        nlohmann_json::nlohmann_json
        tinyxml2
        yaml-cpp::yaml-cpp
)

target_link_directories(
        console_ds
        PRIVATE
        ~/vcpkg/packages/tinyxml2_x64-linux/lib
)

add_subdirectory(lib)
#target_compile_options(mqtt PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-function)
target_compile_options(console_ds PRIVATE -Wall -Wextra -Wno-unused-function)

set_source_files_properties( src/main.c src/interface.c PROPERTIES LANGUAGE CXX)
