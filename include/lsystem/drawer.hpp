//
// Created by one_eyed_john on 18/05/23.
//

#ifndef L_SYSTEMS_DRAWER_HPP
#define L_SYSTEMS_DRAWER_HPP

#include <string>
#include <stack>
#include <lsystem/renderer.hpp>
#include <lsystem/lsystem.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Drawer {
public:
    struct Position {
        float x_;
        float y_;
        float angle_;

        Position(float x, float y, float angle) : x_(x), y_(y), angle_(angle) {};
    };

public:
    explicit Drawer(unsigned int lineLength = 100, float rotationAngle = 30);

    void SetLSystem(LSystem &lSystem);

    void SetLineLength(unsigned int);

    void SetRotationAngle(float);

    void Draw(Renderer &render);

private:
    std::string l_system_{};
    unsigned int line_length_;
    float rotation_angle_;
    std::stack<Position> position_stack_;

    void setStartingPosition();

    void rotateRight();

    void rotateLeft();

    void push();

    void pop();

    void move(Renderer &render);
};

#endif //L_SYSTEMS_DRAWER_HPP
