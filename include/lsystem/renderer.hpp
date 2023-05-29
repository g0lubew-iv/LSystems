//
// Created by one_eyed_john on 22/05/23.
//

#ifndef L_SYSTEMS_RENDERER_HPP
#define L_SYSTEMS_RENDERER_HPP

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

struct GLFWwindow; // just for declaration: GLFWwindow* window_

/**
 * \brief A class for working with OpenGL and rendering LSystems,
 *
 * \param width The width_ of window; default is 500
 * \param height The height_ of window; default is 500
 */
class Renderer {
public:
    /**
     * \brief A struct that defines each line of system
     * \param width The width_ of window; default is 500
     * \param height The height_ of window; default is 500
     */
    struct Line {
        glm::vec2 begin = {0, 0};
        glm::vec2 end = {0, 0};
    };

public:
    /**
     * \brief Initialize all processes: setting up GLFW window, making current context, loading GL
     * \param width The width_ of window; default is 500
     * \param height The height_ of window; default is 500
     */
    explicit Renderer(unsigned int width = 500, unsigned int height = 500);

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
    void Runtime(double upd = 4., double fps = 4.);

private:

    static const int vertex_byte_size_;

    unsigned int buffer_ = 0;
    unsigned int vertex_array_ = 0;
    unsigned int program_ = 0;

    int projection_loc_ = 0;

    glm::mat4 view_{1.f}; // Единичная
    glm::mat4 projection_;

    /// @brief Vector of Lines
    std::vector<Line> lines_vector_ = {};

    /// @brief GLFW: object of window
    GLFWwindow *window_;

    bool dirt = false;

    void rebuild();

    void render();
};

#endif //L_SYSTEMS_RENDERER_HPP
