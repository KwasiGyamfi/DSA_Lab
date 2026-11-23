cmake_minimum_required(VERSION 3.16)

project(LinkedListMediaPlayer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_library(media_core
    src/Song.cpp
    src/Playlist.cpp
)

target_include_directories(media_core PUBLIC include)

add_executable(media_player_app src/main.cpp)

target_link_libraries(media_player_app PRIVATE
    media_core
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

enable_testing()

add_executable(playlist_smoke_test tests/playlist_smoke_test.cpp)
target_link_libraries(playlist_smoke_test PRIVATE media_core)
add_test(NAME PlaylistSmokeTest COMMAND playlist_smoke_test)

add_executable(list_variants_test tests/list_variants_test.cpp)
target_link_libraries(list_variants_test PRIVATE media_core)
add_test(NAME ListVariantsTest COMMAND list_variants_test)

find_package(Catch2 3 REQUIRED)

add_executable(unit_tests
    tests/test_playlist.cpp
)

target_link_libraries(unit_tests PRIVATE
    media_core
    Catch2::Catch2WithMain
)

add_test(NAME Catch2UnitTests COMMAND unit_tests)
# Additional array/linked variants and merge checks
add_executable(extended_tests tests/test_extended.cpp)
target_link_libraries(extended_tests PRIVATE media_core Catch2::Catch2WithMain)
add_test(NAME ExtendedMergeTests COMMAND extended_tests)
add_executable(merge_benchmark tests/benchmark.cpp)
target_link_libraries(merge_benchmark PRIVATE media_core)
add_executable(audio_file_check tests/audio_file_check.cpp)
target_link_libraries(audio_file_check PRIVATE sfml-audio sfml-system)
