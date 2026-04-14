cmake_minimum_required(VERSION 3.28)

target_sources(${PROJECT_NAME}
    PRIVATE
    command.cpp
    parse.cpp
    token.cpp
    parse_token.cpp
)