#include <lsystem/drawer.hpp>

#include <numbers>
#include <cmath>
#include <utility>

Drawer::Drawer(std::string l_system_string, unsigned int line_length, float rotation_angle, unsigned int width,
               unsigned int height) :
        system_out_(std::move(l_system_string)), line_len_(line_length), rot_angle_(rotation_angle), width_(width),
        height_(height) {
    start();
}

void Drawer::start() {
    nodes_stack.emplace(width_, height_, 0);
}

void Drawer::move(Renderer &render) {
    Node site_1 = nodes_stack.top();
    Node site_2 = Node(site_1.x_ + std::sin(site_1.angle_) * static_cast<float>(line_len_),
                       site_1.y_ - std::cos(site_1.angle_) * static_cast<float>(line_len_),
                       site_1.angle_);

    render.DrawLine(glm::vec2(site_1.x_, site_1.y_), glm::vec2(site_2.x_, site_2.y_));

    nodes_stack.pop();
    nodes_stack.push(site_2);
}

void Drawer::move_without_drawing() {
    // Like the move() function, but without call of Renderer
    Node site_1 = nodes_stack.top();
    Node site_2 = Node(site_1.x_ + std::sin(site_1.angle_) * static_cast<float>(line_len_),
                       site_1.y_ - std::cos(site_1.angle_) * static_cast<float>(line_len_),
                       site_1.angle_);

    nodes_stack.pop();
    nodes_stack.push(site_2);
}

void Drawer::turn_right() {
    nodes_stack.top().angle_ += (std::numbers::pi_v<float> * rot_angle_) / 180.f;
}

void Drawer::turn_left() {
    nodes_stack.top().angle_ -= (std::numbers::pi_v<float> * rot_angle_) / 180.f;
}

void Drawer::push() {
    nodes_stack.push(nodes_stack.top());
}

void Drawer::pop() {
    nodes_stack.pop();
}

void Drawer::SetLineLength(unsigned int length) {
    line_len_ = length;
}

void Drawer::SetRotationAngle(float angle) {
    rot_angle_ = angle;
}

void Drawer::Draw(Renderer &render) {
    for (char command_letter: system_out_) {
        // See README.md with a commands list
        switch (command_letter) {
            case 'F':
                move(render);
                break;
            case 'f':
                move_without_drawing();
                break;
            case '+':
                turn_left();
                break;
            case '-':
                turn_right();
                break;
//            case '|':
                // TODO: reverse on 180 degrees?
//                turn_right();
//                break;
            case '[':
                push();
                break;
            case ']':
                pop();
                break;
            default:
                break;
        }
    }
    start();
}
