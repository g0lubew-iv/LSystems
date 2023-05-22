//
// Created by one_eyed_john on 22/05/23.
//

#include <lsystem/renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

Renderer::Renderer(int width, int height) {
    if (!glfwInit()) {
        std::cout << "failed to init glfw\n";
        std::terminate();
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    window_ = glfwCreateWindow(width, height, "LSystem", nullptr, nullptr);

    if (window_ == nullptr) {
        std::cout << "failed to create window\n";
        std::terminate();
    }

    glfwMakeContextCurrent(window_);

    if (!gladLoadGL()) {
        std::cout << "failed to initialize glad\n";
        std::terminate();
    }


}

Renderer::~Renderer() {
    glfwTerminate();
}

void Renderer::DrawLine(glm::vec2 begin, glm::vec2 end) {
    lines.emplace_back(begin, end);
}

void Renderer::render() {

}

void Renderer::Runtime() {
    const double upd_ = 4;
    const double fps_ = 4;

    const double upd_rate_ = 1. / upd_;
    const double fps_rate_ = 1. / fps_;

    double last_time, curr_time = glfwGetTime(),
            upd_time_count = 0,
            fps_time_count = 0;

    bool should_redraw = true;

    while (!glfwWindowShouldClose(window_)) {
        last_time = curr_time;
        curr_time = glfwGetTime();
        auto duration = curr_time - last_time;
        upd_time_count += duration;
        fps_time_count += duration;

        if (should_redraw && fps_time_count >= fps_rate_) {
            fps_time_count -= fps_rate_;
            glClear(GL_COLOR_BUFFER_BIT);
            this->render();
            glfwSwapBuffers(window_);
            should_redraw = false;
        }

        while (upd_time_count >= upd_rate_) {
            upd_time_count -= upd_rate_;
            if (!should_redraw) should_redraw = true;
            glfwPollEvents();
            // TODO: camera's movement
        }
    }
}
