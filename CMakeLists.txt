cmake_minimum_required(VERSION 3.12)

project(boardthing)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(PLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_definitions(PLATFORM_WINDOWS)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(ext/bgfx.cmake)
add_subdirectory(ext/glfw)
add_subdirectory(ext/glm)

add_library(imgui
    ext/imgui/imgui.cpp
    ext/imgui/imgui_draw.cpp
    ext/imgui/imgui_tables.cpp
    ext/imgui/imgui_widgets.cpp
    ext/imgui/imgui_demo.cpp
)

target_include_directories(imgui PUBLIC ext/imgui ext/)

file(GLOB misc
    src/misc/*.cpp
    src/misc/*.h
)
add_executable(boardthing src/main.cpp ${misc})

target_link_libraries(boardthing bgfx bx imgui glfw glm::glm)