//
// Created by one_eyed_john on 22/05/23.
//

#include <lsystem/renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

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
}

Renderer::~Renderer() {
    glfwTerminate();
}

void Renderer::AddLine(glm::vec2 begin, glm::vec2 end) {
    lines_vector.emplace_back(begin, end);
}

void Renderer::render() {
    // TODO: ALL!
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
