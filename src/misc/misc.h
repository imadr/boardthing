// clang-format off
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <GLFW/glfw3.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <string>

#if PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#endif
#include <GLFW/glfw3native.h>

void* get_native_glfw_handle(GLFWwindow* _window) {
#if PLATFORM_WINDOWS
    return glfwGetWin32Window(_window);
#endif
}

#include "misc/imgui_impl_bgfx.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <bx/file.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"