//
// Created by one_eyed_john on 07/06/23.
//

#ifndef L_SYSTEMS_RENDERER_HPP
#define L_SYSTEMS_RENDERER_HPP

#include <vector>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

struct GLFWwindow;

class Renderer {
public:
    explicit Renderer(int width = 800, int height = 800);

    void Runtime(double upd = 60., double fps = 60.);

    ~Renderer();

    void AddLine(glm::vec2 begin, glm::vec2 end);

    void UpdateData();

private:
    GLFWwindow *window = nullptr;
    unsigned int program = 0;
    unsigned int vertex_array = 0;
    unsigned int vertex_buffer = 0;

    glm::mat4 projection{1.f};
    glm::mat4 view{1.f};

    int count_vertices = 0;
    int matrix_location = 0;

    std::vector<glm::vec2> vertices{};

    glm::ivec2 camera_shift = {0, 0};
    float camera_speed = 0.05;
    float scale = 1;
    float scale_speed = 0.000005;

    void render();

    void input();

    void update(double duration);
};


#endif //L_SYSTEMS_RENDERER_HPP
