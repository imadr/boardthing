#include "misc/misc.h"
#include "quad_fragment.bin.h"
#include "quad_vertex.bin.h"

#define VIEW_RENDER 0
#define VIEW_COPY_TO_FRAMEBUFFER 1
#define VIEW_BLIT 2
#define VIEW_IMGUI 3

struct PosTexcoordVertex {
    float x, y, z;
    float u, v;

    static const bgfx::VertexLayout Layout;
};

const bgfx::VertexLayout PosTexcoordVertex::Layout{
    bgfx::VertexLayout()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)};

struct Quad {
    glm::vec3 position = glm::vec3(0, 0, 0);
    float aspect_ratio = 1.0;
    std::string filename;
    glm::vec2 texture_size = glm::vec2(0, 0);
    bgfx::TextureHandle texture_handle;
    glm::vec2 min_corner;
    glm::vec2 max_corner;
    bool mirror_h = false;
    bool mirror_v = false;
    bool deleted = false;
};

struct Context {
    GLFWwindow* window;
    int window_width = 1200;
    int window_height = 900;
    int hovered_quad = -1;
    int selected_quad = -1;
    glm::vec2 drag_start_mouse_pos;
    glm::vec3 drag_start_quad_pos;
    int dragged_quad = -1;

    std::vector<Quad> quads;

    bool was_inside = false;
    float camera_zoom = 3.0;

    bool erase_mode = false;

    bgfx::VertexBufferHandle vertex_buffer_handle;
    bgfx::IndexBufferHandle index_buffer_handle;
    bgfx::ShaderHandle vertex_shader_handle;
    bgfx::ShaderHandle fragment_shader_handle;
    bgfx::ProgramHandle program;
    bgfx::TextureHandle readback_texture_handle;

    glm::mat4 view;
    float aspect_ratio;

    bgfx::UniformHandle uniform_handle;

    bgfx::TextureHandle render_texture_handle;
    bgfx::FrameBufferHandle framebuffer_handle;

    bool readback_next_frame = false;
    bool save_next_available_frame = false;
    uint32_t frame_when_readback_available = 0;
    bool show_saved_notification = false;
    std::vector<uint8_t> pixels;
};
Context ctx;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    ctx.camera_zoom -= (float)yoffset * 0.1f;
    ctx.camera_zoom = glm::clamp(ctx.camera_zoom, 0.001f, 1000.0f);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse) {
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(ctx.window, &xpos, &ypos);

            if (ctx.hovered_quad > -1) {
                ctx.selected_quad = ctx.hovered_quad;
                ctx.dragged_quad = ctx.hovered_quad;
                ctx.drag_start_mouse_pos = glm::vec2(xpos, ypos);
                ctx.drag_start_quad_pos = ctx.quads[ctx.hovered_quad].position;
            } else {
                ctx.selected_quad = -1;
            }
        } else if (action == GLFW_RELEASE) {
            ctx.dragged_quad = -1;
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (ctx.dragged_quad > -1 && !ctx.erase_mode) {
        glm::vec2 current_mouse_pos = glm::vec2(xpos, ypos);
        glm::vec2 delta = current_mouse_pos - ctx.drag_start_mouse_pos;
        delta /= 100.0f;
        ctx.quads[ctx.dragged_quad].position =
            ctx.drag_start_quad_pos + glm::vec3(delta.x, -delta.y, 0);
    }
}

std::function<void()> main_loop = []() {
    glfwPollEvents();

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 mouse_pos = ImGui::GetMousePos();
    glm::vec2 mouse_pos_glm(mouse_pos.x, mouse_pos.y);

    glm::mat4 proj = glm::ortho(-1.0f * ctx.aspect_ratio * ctx.camera_zoom,
                                1.0f * ctx.aspect_ratio * ctx.camera_zoom, -1.0f * ctx.camera_zoom,
                                1.0f * ctx.camera_zoom, 0.0f, 100.0f);

    int i = 0;
    for (auto& quad : ctx.quads) {
        if (quad.deleted) continue;
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, quad.position);
        float scale_x = 1.0;
        float scale_y = 1.0;
        if (i == 0) {
            scale_x = 2.0;
            scale_y = 2.0;
        }
        model = glm::scale(
            model,
            glm::vec3((quad.mirror_h ? -1.0 : 1.0) *
                          (float(quad.texture_size.x) / float(quad.texture_size.y)) * scale_x,
                      (quad.mirror_v ? -1.0 : 1.0) * scale_y, 1.0));
        glm::vec4 corners[4] = {
            glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f), glm::vec4(1.0f, -1.0f, 0.0f, 1.0f),
            glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)};

        glm::mat4 mvp = proj * ctx.view * model;

        for (int i = 0; i < 4; ++i) {
            glm::vec4 clip_space = mvp * corners[i];
            glm::vec2 ndc_space =
                glm::vec2(clip_space.x / clip_space.w, clip_space.y / clip_space.w);
            glm::vec2 screen_space = 0.5f * (ndc_space + glm::vec2(1.0f, 1.0f));
            screen_space *= glm::vec2(ctx.window_width, ctx.window_height);
            screen_space.y = ctx.window_height - screen_space.y;
            if (i == 0) {
                quad.min_corner = glm::vec2(screen_space.x, screen_space.y);
                quad.max_corner = glm::vec2(screen_space.x, screen_space.y);
            } else {
                quad.min_corner =
                    glm::min(quad.min_corner, glm::vec2(screen_space.x, screen_space.y));
                quad.max_corner =
                    glm::max(quad.max_corner, glm::vec2(screen_space.x, screen_space.y));
            }
        }

        bgfx::setViewFrameBuffer(VIEW_RENDER, ctx.framebuffer_handle);
        bgfx::setViewClear(VIEW_RENDER, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
        bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_BLEND_ALPHA);
        bgfx::setViewRect(VIEW_RENDER, 0, 0, uint16_t(ctx.window_width),
                          uint16_t(ctx.window_height));
        bgfx::setViewTransform(VIEW_RENDER, glm::value_ptr(ctx.view), glm::value_ptr(proj));
        bgfx::setVertexBuffer(VIEW_RENDER, ctx.vertex_buffer_handle);
        bgfx::setIndexBuffer(ctx.index_buffer_handle);
        bgfx::setTexture(0, ctx.uniform_handle, quad.texture_handle);
        bgfx::setTransform(glm::value_ptr(model));
        bgfx::submit(VIEW_RENDER, ctx.program);

        if ((mouse_pos_glm.x >= quad.min_corner.x && mouse_pos_glm.x <= quad.max_corner.x &&
             mouse_pos_glm.y >= quad.min_corner.y && mouse_pos_glm.y <= quad.max_corner.y)) {
            ctx.hovered_quad = i;
        }
        i++;
    }

    bgfx::setViewFrameBuffer(VIEW_COPY_TO_FRAMEBUFFER, BGFX_INVALID_HANDLE);
    bgfx::setViewClear(VIEW_COPY_TO_FRAMEBUFFER, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x000000ff,
                       1.0f, 0);
    bgfx::setViewRect(VIEW_COPY_TO_FRAMEBUFFER, 0, 0, uint16_t(ctx.window_width),
                      uint16_t(ctx.window_height));
    bgfx::setVertexBuffer(VIEW_COPY_TO_FRAMEBUFFER, ctx.vertex_buffer_handle);
    bgfx::setTexture(0, ctx.uniform_handle, ctx.render_texture_handle);
    bgfx::setIndexBuffer(ctx.index_buffer_handle);
    bgfx::submit(VIEW_COPY_TO_FRAMEBUFFER, ctx.program);

    if (ctx.readback_next_frame) {
        bgfx::blit(VIEW_BLIT, ctx.readback_texture_handle, 0, 0,
                   bgfx::getTexture(ctx.framebuffer_handle));
        ctx.frame_when_readback_available =
            bgfx::readTexture(ctx.readback_texture_handle, ctx.pixels.data());
        ctx.readback_next_frame = false;
        ctx.save_next_available_frame = true;
    }

    ImGui_ImplGlfw_NewFrame();
    ImGui_Implbgfx_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowSize(ImVec2(300, 150));
    ImGui::Begin("Hello world!");
    ImGui::Text("Welcome to boardthing");
    if (ImGui::Button("Save")) {
        ctx.readback_next_frame = true;
    }
    if (ctx.show_saved_notification) {
        ImGui::Text("Saved canvas to output.png");
    }
    ImGui::End();

    if (ctx.hovered_quad > -1 && !ctx.erase_mode) {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    } else {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
    }

    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    if (ctx.erase_mode) {
        draw_list->AddCircle(mouse_pos, 20, IM_COL32(255, 0, 0, 255), 30, 3.0f);
    }

    if (ctx.selected_quad > -1) {
        draw_list->AddRect(ImVec2(ctx.quads[ctx.selected_quad].min_corner.x - 5,
                                  ctx.quads[ctx.selected_quad].min_corner.y - 5),
                           ImVec2(ctx.quads[ctx.selected_quad].max_corner.x + 5,
                                  ctx.quads[ctx.selected_quad].max_corner.y + 5),
                           IM_COL32(0, 255, 0, 255), 0.0f, 0, 3.0f);

        ImGui::SetNextWindowPos(ImVec2(ctx.quads[ctx.selected_quad].min_corner.x,
                                       ctx.quads[ctx.selected_quad].min_corner.y - 40),
                                ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(0, 0));
        ImGui::Begin("##hidden", nullptr,
                     ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                         ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                         ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);
        if (ImGui::Button("Erase")) {
            ctx.erase_mode = true;
        }
        ImGui::SameLine();
        if (ImGui::Button("Mirror V")) {
            ctx.quads[ctx.selected_quad].mirror_v = !ctx.quads[ctx.selected_quad].mirror_v;
        }
        ImGui::SameLine();
        if (ImGui::Button("Mirror H")) {
            ctx.quads[ctx.selected_quad].mirror_h = !ctx.quads[ctx.selected_quad].mirror_h;
        }
        ImGui::SameLine();
        ImGui::Button("Rotate");
        ImGui::SameLine();
        if (ImGui::Button("Delete")) {
            ctx.quads[ctx.selected_quad].deleted = true;
            ctx.selected_quad = -1;
        }
        ImGui::End();
    }
    ImGui::Render();

    ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

    uint32_t frame_number = bgfx::frame();

    if (ctx.save_next_available_frame && frame_number >= ctx.frame_when_readback_available) {
        stbi_flip_vertically_on_write(true);
        stbi_write_png("output.png", ctx.window_width, ctx.window_height, 4, ctx.pixels.data(),
                       ctx.window_width * 4);
        ctx.save_next_available_frame = false;
        ctx.show_saved_notification = true;
    }
};

void emscripten_main_loop_wrapper() {
    main_loop();
}

// EMSCRIPTEN_KEEPALIVE
// void resize_callback(Context* ctx) {
// }

int main() {
    if (!glfwInit()) {
        printf("[error] failed to initialize GLFW\n");
        return -1;
    }

    ctx.window =
        glfwCreateWindow(ctx.window_width, ctx.window_height, "boardthing", nullptr, nullptr);
    if (!ctx.window) {
        printf("[error] failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(ctx.window);
    // glfwSwapInterval(1);

    glfwSetCursorPosCallback(ctx.window, cursor_position_callback);
    glfwSetMouseButtonCallback(ctx.window, mouse_button_callback);
    glfwSetScrollCallback(ctx.window, scroll_callback);

    bgfx::Init init;

    init.type = bgfx::RendererType::OpenGL;
    init.platformData.nwh = get_native_glfw_handle(ctx.window, ctx.window_width, ctx.window_height);

#ifdef EMSCRIPTEN
    emscripten_set_canvas_element_size("#canvas", ctx.window_width, ctx.window_height);

    // emscripten_set_resize_callback(
    //     EMSCRIPTEN_EVENT_TARGET_WINDOW, &ctx, 0,
    //     [](int even_type, const EmscriptenUiEvent* ui_event, void* user_data) -> EM_BOOL {
    //         Context* ctx = (Context*)user_data;
    //         int width = ui_event->windowInnerWidth;
    //         int height = ui_event->windowInnerHeight;
    //         ctx->window_width = width;
    //         ctx->window_height = height;
    //         // resize_callback(ctx);
    //         return EM_TRUE;
    //     });
#endif

    init.resolution.width = ctx.window_width;
    init.resolution.height = ctx.window_height;
    bgfx::init(init);

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOther(ctx.window, true);
    ImGui_Implbgfx_Init(VIEW_IMGUI);

    bgfx::setViewName(VIEW_RENDER, "VIEW_RENDER");
    bgfx::setViewName(VIEW_COPY_TO_FRAMEBUFFER, "VIEW_COPY_TO_FRAMEBUFFER");
    bgfx::setViewName(VIEW_BLIT, "VIEW_BLIT");
    bgfx::setViewName(VIEW_IMGUI, "VIEW_IMGUI");
    const PosTexcoordVertex quad_vertices[] = {{-1.0f, -1.0f, 0.0f, 0.0f, 0.0f},
                                               {1.0f, -1.0f, 0.0f, 1.0f, 0.0f},
                                               {-1.0f, 1.0f, 0.0f, 0.0f, 1.0f},
                                               {1.0f, 1.0f, 0.0f, 1.0f, 1.0f}};

    const uint16_t quad_indices[] = {0, 1, 2, 1, 3, 2};

    ctx.vertex_buffer_handle = bgfx::createVertexBuffer(
        bgfx::makeRef(quad_vertices, sizeof(quad_vertices)), PosTexcoordVertex::Layout);
    ctx.index_buffer_handle =
        bgfx::createIndexBuffer(bgfx::makeRef(quad_indices, sizeof(quad_indices)));

    ctx.vertex_shader_handle = bgfx::createShader(bgfx::makeRef(quad_vertex, sizeof(quad_vertex)));
    ctx.fragment_shader_handle =
        bgfx::createShader(bgfx::makeRef(quad_fragment, sizeof(quad_fragment)));
    ctx.program = bgfx::createProgram(ctx.vertex_shader_handle, ctx.fragment_shader_handle, true);

    ctx.view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));
    ctx.aspect_ratio = float(ctx.window_width) / float(ctx.window_height);

    ctx.quads.push_back(Quad{glm::vec3(1, 0, 0), 1.0, "assets/guts.jpg", glm::vec2(0, 0),
                             BGFX_INVALID_HANDLE, glm::vec2(0, 0), glm::vec2(1, 1), false, false,
                             false});

    ctx.quads.push_back(Quad{glm::vec3(0, 0, 0), 1.0, "assets/logo.png", glm::vec2(0, 0),
                             BGFX_INVALID_HANDLE, glm::vec2(0, 0), glm::vec2(1, 1), false, false,
                             false});

    ctx.uniform_handle = bgfx::createUniform("texture_uniform", bgfx::UniformType::Sampler);

    for (auto& quad : ctx.quads) {
        int texture_width, texture_height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data =
            stbi_load(quad.filename.c_str(), &texture_width, &texture_height, &channels, 4);
        if (!data) {
            printf("[error] couldn't load logo.png\n");
            return -1;
        }

        bgfx::TextureHandle texture_handle = bgfx::createTexture2D(
            texture_width, texture_height, false, 1, bgfx::TextureFormat::RGBA8, 0,
            bgfx::makeRef(data, texture_width * texture_height * 4));
        quad.texture_handle = texture_handle;
        quad.texture_size = glm::vec2(texture_width, texture_height);
    }

    ctx.render_texture_handle =
        bgfx::createTexture2D(ctx.window_width, ctx.window_height, false, 1,
                              bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT, NULL);
    ctx.framebuffer_handle = bgfx::createFrameBuffer(1, &ctx.render_texture_handle, true);

    ctx.readback_texture_handle = bgfx::createTexture2D(
        ctx.window_width, ctx.window_height, false, 1, bgfx::TextureFormat::RGBA8,
        BGFX_TEXTURE_READ_BACK | BGFX_TEXTURE_BLIT_DST, NULL);
    ctx.pixels = std::vector<uint8_t>(ctx.window_width * ctx.window_height * 4);

#ifdef EMSCRIPTEN
    emscripten_set_main_loop(emscripten_main_loop_wrapper, 0, true);
#else
    while (!glfwWindowShouldClose(ctx.window)) {
        main_loop();
    }
#endif

    ImGui_Implbgfx_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    bgfx::shutdown();
    glfwDestroyWindow(ctx.window);
    glfwTerminate();

    return 0;
}
