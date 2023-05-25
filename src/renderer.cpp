//
// Created by one_eyed_john on 22/05/23.
//

#include <lsystem/renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const int Renderer::vertex_byte_size_ = sizeof(glm::vec2);

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
}

void Renderer::render() {
    for (auto l: lines_vector_) {
        std::cout << l.begin.x << " " << l.begin.y << "; " << l.end.x << " " << l.end.y << "\n";
    }

    auto vertices_count = static_cast<int>(lines_vector_.size() * 2); // Number of all vertices
    glNamedBufferData(buffer_, vertices_count * vertex_byte_size_, nullptr, GL_DYNAMIC_DRAW);

    auto *mapped_ptr = reinterpret_cast<glm::vec2 *>(glMapNamedBuffer(buffer_, GL_WRITE_ONLY));
    for (int i = 0; i < lines_vector_.size(); i += 1) {
        mapped_ptr[i] = lines_vector_[i].begin;
    }
    for (int j = 0; j < lines_vector_.size(); j += 1) {
        mapped_ptr[lines_vector_.size() + j] = lines_vector_[j].end;
    }
    glUnmapNamedBuffer(buffer_);
    glBindVertexArray(vertex_array_);
    glDrawArrays(GL_LINE_STRIP, 0, vertices_count);
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
