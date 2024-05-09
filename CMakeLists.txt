cmake_minimum_required(VERSION 3.16)
project(Final-Project-mclark41.3 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Not using GSL for FFT found it too hard to implement
#[[FetchContent_Declare(gsl
        GIT_REPOSITORY https://github.com/ampl/gsl)
FetchContent_MakeAvailable(gsl)]]

add_executable(CMakeSFMLProject src/main.cpp
        src/Amplitude.cpp
        src/LineAmplitude.cpp
        src/CircleAmplitude.cpp
        src/Home.cpp)

target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics sfml-audio)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET CMakeSFMLProject
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
            VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)
