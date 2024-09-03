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
int hovered_quad = -1;
int selected_quad = -1;
glm::vec2 drag_start_mouse_pos;
glm::vec3 drag_start_quad_pos;
int dragged_quad = -1;

std::vector<Quad> quads;

bool was_inside = false;
float camera_zoom = 3.0;

bool erase_mode = false;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera_zoom -= (float)yoffset * 0.1f;
    camera_zoom = glm::clamp(camera_zoom, 0.001f, 1000.0f);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse) {
        return;
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            if (hovered_quad > -1) {
                selected_quad = hovered_quad;
                dragged_quad = hovered_quad;
                drag_start_mouse_pos = glm::vec2(xpos, ypos);
                drag_start_quad_pos = quads[hovered_quad].position;
            } else {
                selected_quad = -1;
            }
        } else if (action == GLFW_RELEASE) {
            dragged_quad = -1;
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (dragged_quad > -1) {
        glm::vec2 current_mouse_pos = glm::vec2(xpos, ypos);
        glm::vec2 delta = current_mouse_pos - drag_start_mouse_pos;
        delta /= 100.0f;
        quads[dragged_quad].position = drag_start_quad_pos + glm::vec3(delta.x, -delta.y, 0);
    }
}

int main() {
    if (!glfwInit()) {
        printf("[error] failed to initialize GLFW\n");
        return -1;
    }

    int window_width = 1200;
    int window_height = 900;

    GLFWwindow* window =
        glfwCreateWindow(window_width, window_height, "boardthing", nullptr, nullptr);
    if (!window) {
        printf("[error] failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    bgfx::Init init;
    init.type = bgfx::RendererType::OpenGL;
    init.platformData.nwh = get_native_glfw_handle(window);
    init.resolution.width = window_width;
    init.resolution.height = window_height;
    bgfx::init(init);

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOther(window, true);
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

    bgfx::VertexBufferHandle vertex_buffer_handle = bgfx::createVertexBuffer(
        bgfx::makeRef(quad_vertices, sizeof(quad_vertices)), PosTexcoordVertex::Layout);

    bgfx::IndexBufferHandle index_buffer_handle =
        bgfx::createIndexBuffer(bgfx::makeRef(quad_indices, sizeof(quad_indices)));

    bgfx::ShaderHandle vertex_shader_handle =
        bgfx::createShader(bgfx::makeRef(quad_vertex, sizeof(quad_vertex)));
    bgfx::ShaderHandle fragment_shader_handle =
        bgfx::createShader(bgfx::makeRef(quad_fragment, sizeof(quad_fragment)));
    bgfx::ProgramHandle program =
        bgfx::createProgram(vertex_shader_handle, fragment_shader_handle, true);

    glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
    float aspect_ratio = float(window_width) / float(window_height);

    quads.push_back(Quad(glm::vec3(1, 0, 0), 1.0, "guts.jpg", glm::vec2(0, 0)));
    quads.push_back(Quad(glm::vec3(0, 0, 0), 1.0, "logo.png", glm::vec2(0, 0)));

    bgfx::UniformHandle uniform_handle =
        bgfx::createUniform("texture_uniform", bgfx::UniformType::Sampler);

    for (auto& quad : quads) {
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

    bgfx::TextureHandle render_texture_handle = bgfx::createTexture2D(
        window_width, window_height, false, 1, bgfx::TextureFormat::RGBA8, BGFX_TEXTURE_RT, NULL);
    bgfx::FrameBufferHandle framebuffer_handle =
        bgfx::createFrameBuffer(1, &render_texture_handle, true);

    bgfx::TextureHandle readback_texture_handle =
        bgfx::createTexture2D(window_width, window_height, false, 1, bgfx::TextureFormat::RGBA8,
                              BGFX_TEXTURE_READ_BACK | BGFX_TEXTURE_BLIT_DST, NULL);

    bool readback_next_frame = false;
    bool save_next_available_frame = false;
    uint32_t frame_when_readback_available = 0;
    bool show_saved_notification = false;
    std::vector<uint8_t> pixels(window_width * window_height * 4);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGuiIO& io = ImGui::GetIO();
        ImVec2 mouse_pos = ImGui::GetMousePos();
        glm::vec2 mouse_pos_glm(mouse_pos.x, mouse_pos.y);

        glm::mat4 proj =
            glm::ortho(-1.0f * aspect_ratio * camera_zoom, 1.0f * aspect_ratio * camera_zoom,
                       -1.0f * camera_zoom, 1.0f * camera_zoom, 0.0f, 100.0f);

        int i = 0;
        for (auto& quad : quads) {
            if(quad.deleted) continue;
            glm::mat4 model = glm::mat4(1.0);
            model = glm::translate(model, quad.position);
            model = glm::scale(
                model, glm::vec3((quad.mirror_h ? -1.0 : 1.0) * (float(quad.texture_size.x) / float(quad.texture_size.y)),
                                 quad.mirror_v ? -1.0 : 1.0, 1.0));
            glm::vec4 corners[4] = {
                glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f), glm::vec4(1.0f, -1.0f, 0.0f, 1.0f),
                glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)};

            glm::mat4 mvp = proj * view * model;

            for (int i = 0; i < 4; ++i) {
                glm::vec4 clip_space = mvp * corners[i];
                glm::vec2 ndc_space =
                    glm::vec2(clip_space.x / clip_space.w, clip_space.y / clip_space.w);
                glm::vec2 screen_space = 0.5f * (ndc_space + glm::vec2(1.0f, 1.0f));
                screen_space *= glm::vec2(window_width, window_height);
                screen_space.y = window_height - screen_space.y;
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

            bgfx::setViewFrameBuffer(VIEW_RENDER, framebuffer_handle);
            bgfx::setViewClear(VIEW_RENDER, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f,
                               0);
            bgfx::setState(BGFX_STATE_WRITE_RGB | BGFX_STATE_BLEND_ALPHA);
            bgfx::setViewRect(VIEW_RENDER, 0, 0, uint16_t(window_width), uint16_t(window_height));
            bgfx::setViewTransform(VIEW_RENDER, glm::value_ptr(view), glm::value_ptr(proj));
            bgfx::setVertexBuffer(VIEW_RENDER, vertex_buffer_handle);
            bgfx::setIndexBuffer(index_buffer_handle);
            bgfx::setTexture(0, uniform_handle, quad.texture_handle);
            bgfx::setTransform(glm::value_ptr(model));
            bgfx::submit(VIEW_RENDER, program);

            if ((mouse_pos_glm.x >= quad.min_corner.x && mouse_pos_glm.x <= quad.max_corner.x &&
                 mouse_pos_glm.y >= quad.min_corner.y && mouse_pos_glm.y <= quad.max_corner.y)) {
                hovered_quad = i;
            }
            i++;
        }

        bgfx::setViewFrameBuffer(VIEW_COPY_TO_FRAMEBUFFER, BGFX_INVALID_HANDLE);
        bgfx::setViewClear(VIEW_COPY_TO_FRAMEBUFFER, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                           0x000000ff, 1.0f, 0);
        bgfx::setViewRect(VIEW_COPY_TO_FRAMEBUFFER, 0, 0, uint16_t(window_width),
                          uint16_t(window_height));
        bgfx::setVertexBuffer(VIEW_COPY_TO_FRAMEBUFFER, vertex_buffer_handle);
        bgfx::setTexture(0, uniform_handle, render_texture_handle);
        bgfx::setIndexBuffer(index_buffer_handle);
        bgfx::submit(VIEW_COPY_TO_FRAMEBUFFER, program);

        if (readback_next_frame) {
            bgfx::blit(VIEW_BLIT, readback_texture_handle, 0, 0,
                       bgfx::getTexture(framebuffer_handle));
            frame_when_readback_available =
                bgfx::readTexture(readback_texture_handle, pixels.data());
            readback_next_frame = false;
            save_next_available_frame = true;
        }

        ImGui_ImplGlfw_NewFrame();
        ImGui_Implbgfx_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowSize(ImVec2(300, 150));
        ImGui::Begin("Hello world!");
        ImGui::Text("Welcome to boardthing");
        if (ImGui::Button("Save")) {
            readback_next_frame = true;
        }
        if (show_saved_notification) {
            ImGui::Text("Saved canvas to output.png");
        }
        ImGui::End();

        if (hovered_quad > -1) {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
        } else {
            ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
        }

        if (selected_quad > -1) {
            ImDrawList* drawList = ImGui::GetBackgroundDrawList();
            drawList->AddRect(ImVec2(quads[selected_quad].min_corner.x - 5,
                                     quads[selected_quad].min_corner.y - 5),
                              ImVec2(quads[selected_quad].max_corner.x + 5,
                                     quads[selected_quad].max_corner.y + 5),
                              IM_COL32(0, 255, 0, 255), 0.0f, 0, 3.0f);

            ImGui::SetNextWindowPos(
                ImVec2(quads[selected_quad].min_corner.x, quads[selected_quad].min_corner.y - 40),
                ImGuiCond_Always);
            ImGui::SetNextWindowSize(ImVec2(0, 0));
            ImGui::Begin("##hidden", nullptr,
                         ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                             ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
                             ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);
            if (ImGui::Button("Erase")) {
                erase_mode = true;
            }
            if (ImGui::Button("Mirror V")) {
                quads[selected_quad].mirror_v = !quads[selected_quad].mirror_v;
            }
            ImGui::SameLine();
            if (ImGui::Button("Mirror H")) {
                quads[selected_quad].mirror_h = !quads[selected_quad].mirror_h;
            }
            ImGui::SameLine();
            ImGui::Button("Rotate");
            ImGui::SameLine();
            if(ImGui::Button("Delete")){
                quads[selected_quad].deleted = true;
                selected_quad = -1;
            }
            ImGui::End();
        }
        ImGui::Render();

        ImGui_Implbgfx_RenderDrawLists(ImGui::GetDrawData());

        uint32_t frame_number = bgfx::frame();

        if (save_next_available_frame && frame_number >= frame_when_readback_available) {
            stbi_flip_vertically_on_write(true);
            stbi_write_png("output.png", window_width, window_height, 4, pixels.data(),
                           window_width * 4);
            save_next_available_frame = false;
            show_saved_notification = true;
        }
    }

    ImGui_Implbgfx_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    bgfx::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
