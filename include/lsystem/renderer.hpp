//
// Created by one_eyed_john on 22/05/23.
//

#ifndef L_SYSTEMS_RENDERER_HPP
#define L_SYSTEMS_RENDERER_HPP

#include <glm/vec2.hpp>
#include <vector>

struct GLFWwindow;

class Renderer {
public:
    struct Line {
        glm::vec2 begin = {0, 0};
        glm::vec2 end = {0, 0};
    };

public:
    Renderer(int width, int height);

    ~Renderer();

    void DrawLine(glm::vec2 begin, glm::vec2 end);

    void render();

    void Runtime();

private:
    std::vector<Line> lines = {};
    GLFWwindow* window_;
};

#endif //L_SYSTEMS_RENDERER_HPP
