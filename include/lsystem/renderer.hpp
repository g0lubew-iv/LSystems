//
// Created by one_eyed_john on 22/05/23.
//

#ifndef L_SYSTEMS_RENDERER_HPP
#define L_SYSTEMS_RENDERER_HPP

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

struct GLFWwindow; // just for declaration: GLFWwindow *window_

/**
 * \brief A class for working with OpenGL and rendering LSystems,
 *
 * \param width The width of window; default is 500
 * \param height The height of window; default is 500
 */
class Renderer {
public:
    /**
     * \brief Initialize all processes: setting up GLFW window, making current context, loading GL
     * \param window_width The width of window; default is 800
     * \param window_height The height of window; default is 800
     */
    explicit Renderer(int window_width = 800, int window_height = 800);

    /// @brief Terminate GLFW
    ~Renderer();

    Renderer(const Renderer &other) = delete;

    Renderer &operator=(const Renderer &other) = delete;

    Renderer(Renderer &&other) noexcept = delete;

    Renderer &operator=(Renderer &&other) noexcept = delete;

    /**
     * \brief Emplace a Line into back of lines vector
     * \param begin The first point (Node)
     * \param end The second point (Node)
     */
    void AddLine(glm::vec2 begin, glm::vec2 end);

    /**
     * \brief Running a program with loaded UPD and FPS
     * \param upd (default is 4)
     * \param fps (default is 4)
     */
    void Runtime(double upd = 60., double fps = 60.);

private:

    std::vector<glm::vec2> vertices{};

    unsigned int program = 0,
            vertex_buffer = 0,
            vertex_array = 0;

    int matrix_location = 0,
            color_location = 0;

    glm::mat4 projection{1.f};
    glm::mat4 view{1.f};

    /// @brief GLFW: object of window
    GLFWwindow *window;

    glm::ivec2 camera_shift = {0, 0};
    float camera_speed = 0.05;
    float scale = 1;
    float scale_speed = 0.000005;

    void render();

    void input();

    void update(double duration);
};

#endif //L_SYSTEMS_RENDERER_HPP
