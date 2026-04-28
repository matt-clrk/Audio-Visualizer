cmake_minimum_required(VERSION 3.16)
project(AudioVisualizer LANGUAGES CXX)
 
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
 
set(SFML_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib/cmake/SFML")
 
find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio)
include_directories(/opt/homebrew/Cellar/sfml/3.0.2/include)
 
add_executable(AudioVisualizer
    src/main.cpp
    src/Amplitude.cpp
    src/LineAmplitude.cpp
    src/CircleAmplitude.cpp
    src/Home.cpp)
 
target_link_libraries(AudioVisualizer PRIVATE SFML::Graphics SFML::Audio)
target_compile_features(AudioVisualizer PRIVATE cxx_std_17)
 
# Auto-copy songs folder into build directory
add_custom_command(TARGET AudioVisualizer POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/songs
    ${CMAKE_BINARY_DIR}/songs)