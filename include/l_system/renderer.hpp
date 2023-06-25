//
// Created by one_eyed_john on 07/06/23.
//

#ifndef L_SYSTEMS_RENDERER_HPP
#define L_SYSTEMS_RENDERER_HPP

#include <vector>
#include <string>

#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>

struct GLFWwindow;

/**
 * \brief A class for drawing LSystems, works with OpenGL
 */
class Renderer {
public:
    /**
     * \brief Class constructor
     * \param width Width of window
     * \param height Height of window
     */
    explicit Renderer(int width = 800, int height = 800);

    /// @brief Class destructor: deleting program, buffers, terminate GLFW process
    ~Renderer();

    /**
     * \brief The main program loop
     * \param upd Updates Per Second: how many processes update
     * \param fps Frames Per Second: what is drawn to screen
     */
    void Runtime(double upd = 60., double fps = 60.);

    /**
     * \brief Add new section (2 vectors, begin and end)
     * \param begin Coordinates of begin
     * \param end Coordinates of end
     */
    void AddLine(glm::vec2 begin, glm::vec2 end);

    /// @brief Create new data store for buffer of vertices and count number of vertices
    void UpdateData();

private:
    /// @brief Pointer to GLFW window
    GLFWwindow *window = nullptr;

    /// @brief ID of program
    unsigned int program = 0;

    /// @brief ID of array with vertices
    unsigned int vertex_array = 0;

    /// @brief ID of buffer with vertices
    unsigned int vertex_buffer = 0;

    /// @brief Projection matrix; default is identity
    glm::mat4 projection{1.f};

    /// @brief View matrix; default is identity
    glm::mat4 view{1.f};

    /// @brief ID of matrix
    int matrix_location = 0;

    /// @brief Container of vertices
    std::vector<glm::vec2> vertices{};
    int number_vertices = 0;

    /// @brief Camera offset: needed to move across the canvas
    glm::ivec2 camera_shift = {0, 0};
    float camera_speed = 0.05;

    /// @brief Zoom factor: default unit, of course
    float scale = 1;
    float scale_speed = 0.000005;

    /// @brief Rendering
    void render();

    /// @brief Event handling (keystrokes)
    void input();

    /**
     * \brief Updating zoom and camera offset
     * \param duration Button press time
     */
    void update(double duration);

    /**
     * \brief Take a screenshot of the current part of GLFW window
     * \param filename Name of a new screenshot
     */
    void take_screenshot(const char *filename);

    /**
     * \brief Read the previous number of images
     */
    void read_cash();

    /**
     * \brief Write the next number of images
     */
    void write_cash() const;

    /// @brief Counter of number of screenshots
    unsigned int picture_counter = 0;
};


#endif //L_SYSTEMS_RENDERER_HPP
