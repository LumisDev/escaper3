cmake_minimum_required(VERSION 3.16)
project(escaper3 LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
FetchContent_Declare(box2d
    GIT_REPOSITORY https://github.com/erincatto/box2d.git
    GIT_TAG main)
FetchContent_MakeAvailable(box2d)

add_executable(escaper3 src/main.cpp)
target_link_libraries(escaper3 PRIVATE sfml-graphics box2d)
target_compile_features(escaper3 PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET escaper3
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:escaper3>
        VERBATIM)
endif()

install(TARGETS escaper3)
