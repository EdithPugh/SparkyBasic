cmake_minimum_required(VERSION 3.28)

# bad, should remove when program is stable
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(SparkyBasic)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} )
target_compile_options(${PROJECT_NAME}
    PRIVATE
    -Wall
    -Werror
    -Wextra
    -Wpedantic
    -g -O0 -D_GLIBCXX_DEBUG
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE 
    ${wxWidgets_LIBRARIES}
    m
)

set(CMAKE_CXX_STANDARD 17)

target_sources(${PROJECT_NAME}
    PRIVATE
    main.cpp
    replgui_init.cpp
    replgui_on_enter.cpp
    command.cpp
)
add_subdirectory(lexer)