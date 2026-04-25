cmake_minimum_required(VERSION 3.28)
find_program(CLANG_TIDY "clang-tidy")

if(CLANG_TIDY)
    message(STATUS "clang-tidy found at \"${CLANG_TIDY}\".")
    set(CMAKE_CXX_CLANG_TIDY
        ${CLANG_TIDY}
        --checks=-*,bugprone-*,cppcoreguidelines-*,clang-analyzer-*,modernize-*,readability-*
        -warnings-as-errors=*
    )
else()
    message(WARNING "clang-tidy not found.")
endif()

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
    command_list.cpp
)
add_subdirectory(lexer)