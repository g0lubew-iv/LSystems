//
// Created by one_eyed_john on 22/05/23.
//

#include <lsystem/renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <filesystem>

const int Renderer::vertex_byte_size_ = sizeof(glm::vec2);

std::string load_shader_source(const std::filesystem::path& name) {
    auto path = "./shaders" / name;
    auto file = std::ifstream(path);
    std::string line;
    std::string source;
    while (file.good()) {
        std::getline(file, line);
        source += line;
        source += '\n';
    }
    std::cout << "shader source: " << source << '\n';
    return source;
}

unsigned int make_shader(GLenum shader_type, const std::filesystem::path& shader_path) {
    auto shader_source = load_shader_source(shader_path);
    auto shader_source_data = shader_source.c_str();

    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_source_data, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        std::cout << "failed to compile shader\n";
        std::cout << "\tfile: " << shader_path << '\n';
        std::cout << "\tlog: " << info_log << '\n';
        throw std::runtime_error("failed to compile shader");
    }

    return shader;
}

unsigned int make_program(
        const std::filesystem::path& vertex_shader_path,
        const std::filesystem::path& fragment_shader_path) {

    auto vertex_shader = make_shader(GL_VERTEX_SHADER, vertex_shader_path);
    auto fragment_shader = make_shader(GL_FRAGMENT_SHADER, fragment_shader_path);

    auto program = glCreateProgram();

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);

    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(program, 512, nullptr, info_log);
        std::cout << "failed to link program\n";
        std::cout << "\tlog: " << info_log << '\n';
        throw std::runtime_error("failed to link program");
    }

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

Renderer::Renderer(unsigned int width, unsigned int height) {
    if (!glfwInit()) {
        std::cout << "Failed to init GLFW!\n";
        std::terminate();
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window_ = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
                               "LSystem", nullptr, nullptr);

    if (window_ == nullptr) {
        std::cout << "Failed to create window!\n";
        std::terminate();
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGL()) {
        std::cout << "Failed to initialize Glad!\n";
        std::terminate();
    }

    program_ = make_program("simple.vert", "simple.frag");
    projection_loc_ = glGetUniformLocation(program_, "projection");

    projection_ = glm::ortho(0.f, 0.f, static_cast<float>(width), static_cast<float>(height));

    glCreateBuffers(1, &buffer_);
    glCreateVertexArrays(1, &vertex_array_);
    glVertexArrayVertexBuffer(vertex_array_, 0, buffer_, 0, vertex_byte_size_);
    glEnableVertexArrayAttrib(vertex_array_, 0);
    glVertexArrayAttribFormat(vertex_array_, 0, 2, GL_FLOAT, false, 0);
    glVertexArrayAttribBinding(vertex_array_, 0, 0);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vertex_array_);
    glDeleteBuffers(1, &buffer_);

    glfwTerminate();
}

void Renderer::AddLine(glm::vec2 begin, glm::vec2 end) {
    lines_vector_.emplace_back(begin, end);
    dirt = true;
}

void Renderer::rebuild() {
    auto vertices_count = static_cast<int>(lines_vector_.size() * 2); // Number of all vertices
    // резервация памяти
    glNamedBufferData(buffer_, vertices_count * vertex_byte_size_, nullptr, GL_DYNAMIC_DRAW);
    auto *mapped_ptr = reinterpret_cast<glm::vec2 *>(glMapNamedBuffer(buffer_, GL_WRITE_ONLY));
    for (int i = 0; i < lines_vector_.size(); i += 2) {
        *reinterpret_cast<Line*>(mapped_ptr + i) = lines_vector_[i];
    }
    glUnmapNamedBuffer(buffer_);
}

void Renderer::render() {
    if (dirt) {
        dirt = false;
        rebuild();
    }

    auto vertices_count = static_cast<int>(lines_vector_.size() * 2); // Number of all vertices
    glBindVertexArray(vertex_array_);
    glUseProgram(program_);
    glUniformMatrix4fv(projection_loc_, 1, false, glm::value_ptr(projection_));
    glDrawArrays(GL_LINES, 0, vertices_count);
}

void Renderer::Runtime(double upd, double fps) {

    if ((upd <= 0) || (fps <= 0)) {
        throw std::invalid_argument("UPD and FPS must be non-negative!");
    }

    const double upd_ = upd;
    const double fps_ = fps;

    const double upd_rate_ = 1. / upd_;
    const double fps_rate_ = 1. / fps_;

    double last_time,
            curr_time = glfwGetTime(),
            upd_time_count = 0,
            fps_time_count = 0;

    bool should_redraw = true; // we have to draw figure at the first time

    while (!glfwWindowShouldClose(window_)) {
        last_time = curr_time;
        curr_time = glfwGetTime();

        auto duration = curr_time - last_time;

        upd_time_count += duration;
        fps_time_count += duration;

        if (should_redraw && fps_time_count >= fps_rate_) {
            fps_time_count -= fps_rate_;
            glClear(GL_COLOR_BUFFER_BIT);
            
            this->render(); // rendering!

            glfwSwapBuffers(window_);
            should_redraw = false;
        }

        while (upd_time_count >= upd_rate_) {
            upd_time_count -= upd_rate_;
            if (!should_redraw) {
                should_redraw = true;
            }
            glfwPollEvents();
            // TODO: camera's movement
        }
    }
}
