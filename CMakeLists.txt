cmake_minimum_required(VERSION 3.5.0)

project(palindrome VERSION 1.0.0 LANGUAGES C)

include(CTest)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pipe -std=c99")

add_executable(palindrome.exe src/main.c src/palindrome.c)

add_definitions(-DDEBUG -DREAL_COOL_ENGINEER)

add_compile_options(-Wall -Wextra -pedantic -Werror)

target_include_directories(palindrome.exe PUBLIC ${CMAKE_SOURCE_DIR}/ins )

enable_testing()

include(CPack)