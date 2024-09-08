cmake_minimum_required(VERSION 3.12)

project(boardthing)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_compile_definitions(PLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_compile_options("/utf-8")
    add_compile_definitions(PLATFORM_WINDOWS)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBGFX_CONFIG_MULTITHREADED=0")

    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -gsource-map")
    set(CMAKE_BUILD_TYPE Debug)
endif()


set(SHADERC_PATH "" CACHE FILEPATH "Path to shaderc executable")
set(BGFX_INCLUDE_PATH "" CACHE PATH "Path to BGFX include directory")
set(BGFX_VARYING_DEF_PATH "" CACHE FILEPATH "Path to BGFX varying.def.sc file")

function(compile_shader SHADER_NAME SHADER_TYPE)
    set(SHADER_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/${SHADER_NAME}.glsl")
    set(SHADER_OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/src/${SHADER_NAME}.bin.h")

    add_custom_target(
        compile_${SHADER_NAME}
        COMMAND "${SHADERC_PATH}"
        ARGS -f ${SHADER_SOURCE}
             -o ${SHADER_OUTPUT}
             --type ${SHADER_TYPE}
             --profile 320_es
             -i "${BGFX_INCLUDE_PATH}"
             --varyingdef "${BGFX_VARYING_DEF_PATH}"
             --bin2c
        COMMENT "Compiling shader ${SHADER_NAME}"
        DEPENDS ${SHADER_SOURCE}
    )
    add_dependencies(boardthing compile_${SHADER_NAME})

    set_source_files_properties(${SHADER_OUTPUT} PROPERTIES GENERATED TRUE)
    target_sources(boardthing PRIVATE ${SHADER_OUTPUT})
endfunction()

set(BGFX_BUILD_EXAMPLES OFF)
add_subdirectory(ext/bgfx.cmake)
set(BGFX_BUILD_EXAMPLES OFF)

if(EMSCRIPTEN)
    set(CMAKE_EXECUTABLE_SUFFIX ".js")
    set(PLATFORM_WEB 1)
    add_compile_definitions(EMSCRIPTEN)
else()
    add_subdirectory(ext/glfw)
endif()

add_subdirectory(ext/glm)

add_library(imgui
    ext/imgui/imgui.cpp
    ext/imgui/imgui_draw.cpp
    ext/imgui/imgui_tables.cpp
    ext/imgui/imgui_widgets.cpp
    ext/imgui/imgui_demo.cpp
)

target_include_directories(imgui PUBLIC ext/imgui ext/)

set(misc
    src/misc/fs_ocornut_imgui.bin.h
    src/misc/imgui_impl_bgfx.cpp
    src/misc/imgui_impl_bgfx.h
    src/misc/imgui_impl_glfw.cpp
    src/misc/imgui_impl_glfw.h
    src/misc/misc.h
    src/misc/stb_image.h
    src/misc/stb_image_write.h
    src/misc/vs_ocornut_imgui.bin.h
)

add_executable(boardthing src/main.cpp ${misc})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Emscripten")
    target_link_libraries(boardthing bgfx bx imgui glm::glm)
else()
    target_link_libraries(boardthing bgfx bx imgui glfw glm::glm)
endif()

if(EMSCRIPTEN)
    set(SOURCE_MAP_BASE "http://localhost:8000/")
    set_target_properties(boardthing PROPERTIES LINK_FLAGS "-s USE_PTHREADS=0 -s USE_GLFW=3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1 -s ASSERTIONS=1 -gsource-map --source-map-base=${SOURCE_MAP_BASE} --preload-file ${CMAKE_SOURCE_DIR}/assets@/assets")
endif()

compile_shader(quad_vertex vertex)
compile_shader(quad_fragment fragment)
