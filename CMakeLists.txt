cmake_minimum_required(VERSION 3.21)
project(Backet LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Set the source and destination directories
set(SOURCEDIR "resources")
set(DESTINATIONDIR "${CMAKE_BINARY_DIR}/")

# Only copy files with the ".png" extension from the resources directory
file(COPY ${SOURCEDIR} DESTINATION ${DESTINATIONDIR}
     FILES_MATCHING PATTERN "*.png")

add_executable(Backet src/main.cpp)
target_link_libraries(Backet PRIVATE sfml-graphics)
target_compile_features(Backet PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Backet POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Backet> $<TARGET_FILE_DIR:Backet> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Backet)
