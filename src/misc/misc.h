#pragma once

// clang-format off
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <imgui.h>
#include <string>
#include <bx/file.h>


#if PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#endif

#ifdef EMSCRIPTEN
#include <emscripten.h>
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES3/gl2ext.h>
#include <emscripten/html5.h>
#else
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#endif

void* get_native_glfw_handle(GLFWwindow* window, int width, int height) {
#if PLATFORM_WINDOWS
    return glfwGetWin32Window(window);
#elif EMSCRIPTEN
    EmscriptenWebGLContextAttributes attributes;
    emscripten_webgl_init_context_attributes(&attributes);
    attributes.alpha = false;
    attributes.depth = true;
    attributes.stencil = true;
    attributes.antialias = true;
    attributes.premultipliedAlpha = false;
    attributes.preserveDrawingBuffer = false;
    attributes.powerPreference = EM_WEBGL_POWER_PREFERENCE_HIGH_PERFORMANCE;
    attributes.failIfMajorPerformanceCaveat = false;
    attributes.majorVersion = 2;
    attributes.minorVersion = 0;
    attributes.enableExtensionsByDefault = true;

    int context = emscripten_webgl_create_context("#canvas", &attributes);
    if (!context) {
        printf("[error] failed to create WebGL context");
        return NULL;
    }

    emscripten_webgl_make_context_current(context);
    return (void*)"#canvas";
#endif

}

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>

#include "imgui_impl_bgfx.h"
#include "imgui_impl_glfw.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <functional>

#include "stb_image_write.h"