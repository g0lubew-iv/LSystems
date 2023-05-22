#include <lsystem/drawer.hpp>
#include <lsystem/renderer.hpp>
#include <lsystem/lsystem.hpp>
#include <cmath>
#include <utility>

#include <glm/vec2.hpp>

Drawer::Drawer(unsigned int lineLength, float angle) : line_length_(lineLength), rotation_angle_(angle) {
    setStartingPosition();
}

void Drawer::setStartingPosition() {
    position_stack_.emplace(300, 300, 0);
}

void Drawer::move(Renderer &renderer) {
    Position pos = position_stack_.top();
    Position next_pos = Position(pos.x_ + static_cast<float>(line_length_) * std::sin(pos.angle_),
                                pos.y_ - static_cast<float>(line_length_) * std::cos(pos.angle_),
                                 pos.angle_);

    renderer.DrawLine(glm::vec2(pos.x_, pos.y_), glm::vec2(next_pos.x_, next_pos.y_));

    position_stack_.pop();
    position_stack_.push(next_pos);
}

void Drawer::rotateRight() {
    position_stack_.top().angle_ += M_PI * rotation_angle_ / 180;
}

void Drawer::rotateLeft() {
    position_stack_.top().angle_ -= M_PI * rotation_angle_ / 180;
}

void Drawer::push() {
    position_stack_.push(position_stack_.top());
}

void Drawer::pop() {
    position_stack_.pop();
}

void Drawer::SetLSystem(LSystem &lSystem) {
    this->l_system_ = lSystem.GetString();
}

void Drawer::SetLineLength(unsigned int length) {
    line_length_ = length;
}

void Drawer::SetRotationAngle(float angle) {
    this->rotation_angle_ = angle;
}

void Drawer::Draw(Renderer &render) {
    for (char i : l_system_) {
        switch (i) {
            case 'F':
                move(render);
                break;
            case '+':
                rotateRight();
                break;
            case '-':
                rotateLeft();
                break;
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
    setStartingPosition();
}
