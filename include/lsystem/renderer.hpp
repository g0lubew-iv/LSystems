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
     * \param window_width The width of window; default is 500
     * \param window_height The height of window; default is 500
     */
    explicit Renderer(unsigned int window_width = 500, unsigned int window_height = 500);

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

    static const int vertex_byte_size_;

    unsigned int program_ = 0;
    unsigned int vertex_array_ = 0;
    unsigned int vertex_buffer_ = 0;

    int matrix_location_ = 0;
    int color_location_ = 0;

    glm::mat4 view_{1.f};
    glm::mat4 projection_{1.f};

    /// @brief Vector of Lines
    std::vector<glm::vec2> vertices_ = {};

    /// @brief GLFW: object of window
    GLFWwindow *window_;

    glm::ivec2 camera_shift_ = {0, 0};
    float camera_speed_ = 0.05;
    float scale_ = 1;
    float scale_speed_ = 0.000005;

    void render();

    void input(GLFWwindow *window);

    void update(double duration);
};

#endif //L_SYSTEMS_RENDERER_HPP
