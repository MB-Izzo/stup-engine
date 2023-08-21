# may be a nice example instead of mine:
# https://github.com/Dav1dde/glad/issues/251

cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_C_COMPILER "gcc")

# =================================================================
# ENGINE
# =================================================================
project(StupEngine VERSION 1.0
        DESCRIPTION "Battler game engine"
        LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}/${PROJECT_NAME})

set(IncludeDir_GLFW "${CMAKE_SOURCE_DIR}/StupEngine/vendor/glfw/include")
set(IncludeDir_GLAD "${CMAKE_SOURCE_DIR}/StupEngine/vendor/glad/include")
set(IncludeDir_STB_IMAGE "${CMAKE_SOURCE_DIR}/StupEngine/vendor/stb_image")

add_subdirectory(StupEngine/vendor/glfw) # built with CMakeLists.txt
add_subdirectory(StupEngine/vendor/glad) # '''''

#file(GLOB MyCPPSources ${CMAKE_SOURCE_DIR}/BattlerEngine/src/*.cpp)

# Creates a static lib
add_executable(${PROJECT_NAME})
add_compile_definitions(GLFW_INCLUDE_NONE)

# Add source files 
target_sources(${PROJECT_NAME}
        PRIVATE
    "${CMAKE_SOURCE_DIR}/StupEngine/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/stuppch.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Application.cpp"

    # =============
    # Engine Folder
    # =============
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/Renderer/Renderer.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/Renderer/Window.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/Renderer/Shader.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/Renderer/Texture.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/Renderer/Framebuffer.cpp"

    # Engine/Core
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/Core/Layer.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/Core/Input.cpp"

    # Engine / GameObjects
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/GameObjects/GameObject.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/GameObjects/Scene.cpp"


    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/GameObjects/Components/Sprite.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/GameObjects/Components/Component.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/GameObjects/Components/Transform.cpp"
    "${CMAKE_SOURCE_DIR}/StupEngine/src/Engine/GameObjects/Components/Rigidbody.cpp"
)

# Tell where include files are
target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_SOURCE_DIR}/StupEngine/src"
        ${IncludeDir_GLFW}
        ${IncludeDir_GLAD}
        ${IncludeDir_STB_IMAGE}
)

# Link glad and glfw to lib
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glad
)

# =================================================================
# TEST GAME
# =================================================================
#[===[
add_executable(TestGame)

target_sources(TestGame PRIVATE
    "TestGame/src/main.cpp"
)

target_include_directories(TestGame PUBLIC
    "${CMAKE_SOURCE_DIR}/StupEngine/src"
    "${CMAKE_SOURCE_DIR}/StupEngine/vendor"
    "${CMAKE_SOURCE_DIR}/TestEngine/src"
    # may add GLM here
)

target_link_libraries(TestGame PRIVATE
    ${PROJECT_NAME}
)
]===]
