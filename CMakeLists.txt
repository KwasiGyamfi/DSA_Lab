cmake_minimum_required(VERSION 3.16)

project(MemoryGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(Curses REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(memory_game
    src/main.cpp
    src/memory_game.cpp
    src/linked_list.cpp
)

target_include_directories(memory_game PRIVATE ${CURSES_INCLUDE_DIRS})
target_link_libraries(memory_game PRIVATE
    ${CURSES_LIBRARIES}
    sfml-graphics
    sfml-window
    sfml-system
)

