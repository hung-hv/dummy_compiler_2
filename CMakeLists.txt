cmake_minimum_required(VERSION 3.15)
project (compiler)

include_directories(include)

set(SOURCES src/main.c src/lexer.c src/parser.c src/emitter.c)

add_executable(compiler ${SOURCES})