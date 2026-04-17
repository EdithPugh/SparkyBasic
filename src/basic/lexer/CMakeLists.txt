cmake_minimum_required(VERSION 3.28)

target_sources(${PROJECT_NAME}
    PRIVATE
    lex_line.cpp
    lex_token.cpp
    lex_literals.cpp
    token.cpp
)