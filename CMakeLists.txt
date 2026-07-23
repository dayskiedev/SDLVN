# initial build: cmake -S . -B build
# cmake --build build     				  < Debug
# cmake --build build --config Release    < Release (VS build mode)
# then run with ./build/debug/ace.exe

cmake_minimum_required(VERSION 3.14)
project(SDLVN)

# Set C++ standard (C++17 is a solid default for modern development)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the FetchContent module
include(FetchContent)

# check if we're in release then remove 

# -----------------------------------------------------------------------------
# 1. SDL2 Core
# -----------------------------------------------------------------------------
find_package(SDL2 QUIET)
if(NOT SDL2_FOUND)
    message(STATUS "SDL2 not found locally. Fetching from GitHub...")
    FetchContent_Declare(
        SDL2
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG        release-2.30.2
    )
    FetchContent_MakeAvailable(SDL2)
endif()

# -----------------------------------------------------------------------------
# 2. SDL2_image
# -----------------------------------------------------------------------------
find_package(SDL2_image QUIET)
if(NOT SDL2_image_FOUND)
    message(STATUS "SDL2_image not found locally. Fetching from GitHub...")
    FetchContent_Declare(
        SDL2_image
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
        GIT_TAG        release-2.8.2
    )
    FetchContent_MakeAvailable(SDL2_image)
endif()

# -----------------------------------------------------------------------------
# 3. SDL2_mixer
# -----------------------------------------------------------------------------
find_package(SDL2_mixer QUIET)
if(NOT SDL2_mixer_FOUND)
    message(STATUS "SDL2_mixer not found locally. Fetching from GitHub...")
    FetchContent_Declare(
        SDL2_mixer
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
        GIT_TAG        release-2.8.0
    )
    FetchContent_MakeAvailable(SDL2_mixer)
endif()

# -----------------------------------------------------------------------------
# 4. SDL2_ttf
# -----------------------------------------------------------------------------
find_package(SDL2_ttf QUIET)
if(NOT SDL2_ttf_FOUND)
    message(STATUS "SDL2_ttf not found locally. Fetching from GitHub...")
    FetchContent_Declare(
        SDL2_ttf
        GIT_REPOSITORY https://github.com/libsdl-org/SDL_ttf.git
        GIT_TAG        release-2.22.0
    )
    FetchContent_MakeAvailable(SDL2_ttf)
endif()

# -----------------------------------------------------------------------------
# Build the Executable
# -----------------------------------------------------------------------------
# Ensure you have a main.cpp in the same directory as this CMakeLists.txt
add_executable(SDLVN)

# add all game files
target_sources(SDLVN
    PRIVATE
        src/AnimationManager.cpp
        src/AudioManager.cpp
        src/Button.cpp
        src/Config.cpp
        src/Game.cpp
        src/GameManager.cpp
        src/Interpreter.cpp
        src/Load.cpp
        src/main.cpp
        src/Menu.cpp
        src/OptionsUI.cpp
        src/SaveLoadUI.cpp
        src/SaveManager.cpp
        src/Sprite.cpp
        src/SpriteManager.cpp
        src/Text.cpp
        src/TextManager.cpp
        src/Texture.cpp
        src/UIManager.cpp
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            src/include
        FILES
            src/include/AnimationManager.h
            src/include/AudioManager.h
            src/include/Button.h
            src/include/Config.h
            src/include/Game.h
            src/include/GameManager.h
            src/include/Interpreter.h
            src/include/Load.h
            src/include/Menu.h
            src/include/OptionsUI.h
            src/include/SaveLoadUI.h
            src/include/SaveManager.h
            src/include/Sprite.h
            src/include/SpriteManager.h
            src/include/Text.h
            src/include/TextManager.h
            src/include/Texture.h
            src/include/UIManager.h
)


# Link all the targets. CMake handles the include directories automatically!
target_link_libraries(SDLVN PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
)

# copy all required files / folders over to launch
add_custom_command(
	TARGET SDLVN
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:SDL2::SDL2>
		$<TARGET_FILE_DIR:SDLVN>
)

add_custom_command(
	TARGET SDLVN
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:SDL2_mixer::SDL2_mixer>
		$<TARGET_FILE_DIR:SDLVN>
)

add_custom_command(
	TARGET SDLVN
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:SDL2_image::SDL2_image>
		$<TARGET_FILE_DIR:SDLVN>
)

add_custom_command(
	TARGET SDLVN
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
		$<TARGET_FILE:SDL2_ttf::SDL2_ttf>
		$<TARGET_FILE_DIR:SDLVN>
)

# copy assets over
add_custom_command(
	TARGET SDLVN
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/assets
		$<TARGET_FILE_DIR:SDLVN>/assets
)

