set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_minimum_required(VERSION 3.8)

project(NativeTest)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/App.cpp
    src/IndexBuffer.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/std_image/std_image.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_11)

# Disable GLM_TEST
set(GLM_TEST_ENABLE OFF CACHE BOOL "Build test programs" FORCE)
target_include_directories(NativeTest PRIVATE src)

# Enable many good warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /WX /W3)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wimplicit-fallthrough)
endif()

# Set the folder where the executable is created
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})

# Prevents compiler-specific extensions to C++ because they might allow code to compile on your machine but not on other people's machine
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF)

# Add all the files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*)
target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/App.cpp
    src/IndexBuffer.cpp
    src/Renderer.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/VertexArray.cpp
    src/VertexBuffer.cpp
    src/std_image/std_image.cpp
)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# ---Add GLFW---
add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
# ---Add glad---
add_library(glad lib/glad/src/glad.c)
target_include_directories(glad PUBLIC lib/glad/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# Copy the assets to the output folder (where the executable is created)
include("lib/CMakeUtils/files_and_folders.cmake")
Cool__target_copy_folder(${PROJECT_NAME} "assets")
