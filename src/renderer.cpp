//
// Created by one_eyed_john on 07/06/23.
//

#include "lsystem/renderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>

void glDebugOutput(GLenum source,
                   GLenum type,
                   GLuint id,
                   GLenum severity,
                   GLsizei,
                   const GLchar *message,
                   const void *
) {
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::cout << "---------------\n";
    std::cout << "Debug message (" << id << "): " << message << '\n';

    std::cout << "Source: ";
    switch (source) {
        case GL_DEBUG_SOURCE_API:
            std::cout << "API";
            break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            std::cout << "Window System";
            break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            std::cout << "Shader Compiler";
            break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            std::cout << "Third Party";
            break;
        case GL_DEBUG_SOURCE_APPLICATION:
            std::cout << "Application";
            break;
        case GL_DEBUG_SOURCE_OTHER:
            std::cout << "Other";
            break;
        default:
            std::cout << "Unknown";
    }
    std::cout << '\n';

    std::cout << "Type: ";
    switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            std::cout << "Error";
            break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            std::cout << "Deprecated Behaviour";
            break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            std::cout << "Undefined Behaviour";
            break;
        case GL_DEBUG_TYPE_PORTABILITY:
            std::cout << "Portability";
            break;
        case GL_DEBUG_TYPE_PERFORMANCE:
            std::cout << "Performance";
            break;
        case GL_DEBUG_TYPE_MARKER:
            std::cout << "Marker";
            break;
        case GL_DEBUG_TYPE_PUSH_GROUP:
            std::cout << "Push Group";
            break;
        case GL_DEBUG_TYPE_POP_GROUP:
            std::cout << "Pop Group";
            break;
        case GL_DEBUG_TYPE_OTHER:
            std::cout << "Other";
            break;
        default:
            std::cout << "Unknown";
    }
    std::cout << '\n';

    std::cout << "Severity: ";
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            std::cout << "High";
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cout << "Medium";
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "Low";
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "Notification";
            break;
        default:
            std::cout << "Unknown";
    }
    std::cout << '\n' << std::endl;
}

GLFWwindow *create_window(int width, int height) {
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
    // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    auto window = glfwCreateWindow(width, height,
                                   "lines", nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "Failed to create window!\n";
        std::terminate();
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL()) {
        std::cout << "Failed to initialize Glad!\n";
        std::terminate();
    }

    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        std::cout << "OpenGL debug enabled\n";
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
    }

    return window;
}

std::string load_shader_source(const std::filesystem::path &file_name) {
    auto path = "./shaders" / file_name;
    auto file = std::ifstream(path);
    std::string source, line;
    while (file.good()) {
        std::getline(file, line);
        source += line;
        source += '\n';
    }
    return source;
}

unsigned int make_shader(GLenum type, const std::filesystem::path &file_name) {
    auto source = load_shader_source(file_name);
    unsigned int shader = glCreateShader(type);
    const char *data = source.c_str();
    glShaderSource(shader, 1, &data, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, nullptr, info_log);
        std::cout << "failed to compile shader\n";
        std::cout << "\tfile: " << file_name << '\n';
        std::cout << "\tlog: " << info_log << '\n';
        throw std::runtime_error("failed to compile shader");
    }
    return shader;
}

unsigned int make_program(
        const std::filesystem::path &vert_file_name,
        const std::filesystem::path &frag_file_name) {
    auto vertex_shader = make_shader(GL_VERTEX_SHADER, vert_file_name);
    auto fragment_shader = make_shader(GL_FRAGMENT_SHADER, frag_file_name);
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

Renderer::Renderer(int width, int height) {
    window = create_window(width, height);
    program = make_program("vert.glsl", "frag.glsl");

    glUseProgram(program);
    int color = glGetUniformLocation(program, "color");
    glUniform3f(color, 1, 0, 0);

    matrix_location = glGetUniformLocation(program, "matrix");
    auto x_val = static_cast<float>(width) / 2;
    auto y_val = static_cast<float>(height) / 2;
    projection = glm::ortho(-x_val, x_val, -y_val, y_val);

    glCreateBuffers(1, &vertex_buffer);

    glCreateVertexArrays(1, &vertex_array);

    // attach buffer
    glVertexArrayVertexBuffer(vertex_array, 0, vertex_buffer, 0, sizeof(glm::vec2));

    // configure vertex attribute
    glEnableVertexArrayAttrib(vertex_array, 0);
    glVertexArrayAttribFormat(vertex_array, 0, 2, GL_FLOAT, false, 0);
    glVertexArrayAttribBinding(vertex_array, 0, 0);
}

Renderer::~Renderer() {
    glDeleteProgram(program);
    glDeleteVertexArrays(1, &vertex_array);
    glDeleteBuffers(1, &vertex_buffer);
    glfwTerminate();
}

void Renderer::AddLine(glm::vec2 begin, glm::vec2 end) {
    vertices.push_back(begin);
    vertices.push_back(end);
}

void Renderer::UpdateData() {
    glNamedBufferData(
            vertex_buffer,
            static_cast<int>(sizeof(glm::vec2) * vertices.size()),
            vertices.data(),
            GL_STATIC_DRAW
    );
    count_vertices = static_cast<int>(vertices.size());
}

void Renderer::Runtime(double upd, double fps) {
    const double fps_rate = 1. / fps, upd_rate = 1. / upd;
    double last_time,
            curr_time = glfwGetTime(),
            fps_time_count = 0,
            upd_time_count = 0;
    bool should_redraw = false;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        input();
        last_time = curr_time;
        curr_time = glfwGetTime();
        auto duration = curr_time - last_time;
        fps_time_count += duration;
        upd_time_count += duration;
        while (upd_time_count >= upd_rate) {
            upd_time_count -= upd_rate;
            update(upd_rate);
            should_redraw = true;
        }
        if (should_redraw && fps_time_count >= fps_rate) {
            glClear(GL_COLOR_BUFFER_BIT);
            render();
            glfwSwapBuffers(window);
            while (fps_time_count >= fps_rate)
                fps_time_count -= fps_rate;
            should_redraw = false;
        }
    }
}

void Renderer::render() {
    glUseProgram(program);
    auto matrix = projection * view;
    glUniformMatrix4fv(matrix_location, 1, false, glm::value_ptr(matrix));
    glBindVertexArray(vertex_array);
    glDrawArrays(GL_LINES, 0, count_vertices);
}

void Renderer::input() {
    if (glfwGetKey(window, GLFW_KEY_W)) {
        camera_shift.y -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        camera_shift.y += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_A)) {
        camera_shift.x += 1;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        camera_shift.x -= 1;
    }
    if (glfwGetKey(window, GLFW_KEY_E)) {
        scale += scale_speed;
    }
    if (glfwGetKey(window, GLFW_KEY_Q)) {
        scale -= scale_speed;
        if (scale <= 0)
            scale = scale_speed;
    }
}

void Renderer::update(double duration) {
    view = glm::mat4(1.f);
    auto scale_val = 1 / scale;
    view = glm::scale(view, glm::vec3(scale_val, scale_val, 0));
    auto shift = glm::vec2(camera_shift) * static_cast<float>(duration) * camera_speed;
    view = glm::translate(view, glm::vec3(shift, 0));
}