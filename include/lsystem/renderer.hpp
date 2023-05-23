//
// Created by one_eyed_john on 22/05/23.
//

#ifndef L_SYSTEMS_RENDERER_HPP
#define L_SYSTEMS_RENDERER_HPP

#include <glm/vec2.hpp>
#include <vector>

struct GLFWwindow; // just for declaration: GLFWwindow* window_

/**
 * \brief A class for working with OpenGL and rendering LSystems,
 *
 * \param width The width of window; default is 500
 * \param height The height of window; default is 500
 */
class Renderer {
public:
    /**
     * \brief A struct that defines each line of system
     * \param width The width of window; default is 500
     * \param height The height of window; default is 500
     */
    struct Line {
        glm::vec2 begin = {0, 0};
        glm::vec2 end = {0, 0};
    };

public:
    /**
     * \brief Initialize all processes: setting up GLFW window, making current context, loading GL
     * \param width The width of window; default is 500
     * \param height The height of window; default is 500
     */
    explicit Renderer(unsigned int width = 500, unsigned int height = 500);

    /// @brief Terminate GLFW
    ~Renderer();

    /**
     * \brief Emplace a Line into back of lines vector
     * \param begin The first point (Node)
     * \param end The second point (Node)
     */
    void AddLine(glm::vec2 begin, glm::vec2 end);

    /**
     * \brief ?
     */
    void render();

    /**
     * \brief Running a program with loaded UPD and FPS
     * \param upd (default is 4)
     * \param fps (default is 4)
     */
    void Runtime(double upd = 4., double fps = 4.);

private:
    /// @brief Vector of Lines
    std::vector<Line> lines_vector = {};

    /// @brief GLFW: object of window
    GLFWwindow* window_;
};

#endif //L_SYSTEMS_RENDERER_HPP
