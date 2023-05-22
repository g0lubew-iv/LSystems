//
// Created by one_eyed_john on 26/04/23.
//

#include <iostream>

#include <lsystem/lsystem.hpp>
#include <lsystem/drawer.hpp>
#include <lsystem/renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char *vertex_shader_source =
        "#version 330 core\n"
        "layout (location = 0) in vec2 position;\n"
        "void main() {\n"
        "   gl_Position = vec4(position, 0, 1);\n"
        "}\0";

const char *fragment_shader_source =
        "#version 330 core\n"
        "out vec4 color;\n"
        "void main() {\n"
        "   color = vec4(1, 0.8, 0.1, 1);\n"
        "}\n\0";

struct Vertex {
    float x;
    float y;
};

int main() {
    auto l_s = LSystem();
    l_s.SetAxiom("0");
    l_s.AddRule('1', "11");
    l_s.AddRule('0', "1A0");

    auto renderer = Renderer(600, 600);
    auto drawer = Drawer();

    drawer.SetLSystem(l_s);
    drawer.SetLineLength(2);
    drawer.Draw(renderer);

    renderer.Runtime();

    return 0;
}
