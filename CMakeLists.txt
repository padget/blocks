cmake_minimum_required(VERSION 3.16)
project(blocks C)

set(CMAKE_C_STANDARD 11)

include_directories(blocks)
include_directories(std)
include_directories(std/i18n)

add_executable(blocks
        blocks/clean.c
        blocks/clean.h
        blocks/compile.c
        blocks/compile.h
        blocks/execute.c
        blocks/execute.h
        blocks/main.c
        std/__tests__/stringtest.c
        std/i18n/i18n_en.h
        std/i18n/i18n_fr.h
        std/algorithm.c
        std/algorithm.h
        std/argument.c
        std/argument.h
        std/array.c
        std/array.h
        std/blocks-std.c
        std/blocks-std.h
        std/config.h
        std/i18n.h
        std/keyword.h
        std/log.c
        std/log.h
        std/stdchar.c
        std/stdchar.h
        std/string.c
        std/string.h
        std/utest.c
        std/utest.h
        std/version.h)
