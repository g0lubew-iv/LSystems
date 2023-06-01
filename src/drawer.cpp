#include <lsystem/drawer.hpp>

#include <numbers>
#include <cmath>
#include <utility>

Drawer::Drawer(std::string l_system_string, double line_length, double rotation_angle) :
        l_system_(std::move(l_system_string)), line_length_(line_length), rotation_angle_(rotation_angle) {
}

void Drawer::move_node(Renderer &render, bool should_draw) {
    auto site_1 = nodes_stack.top();
    auto site_2 = Node{
            glm::vec2{
                    site_1.point.x + std::sin(site_1.angle) * line_length_,
                    site_1.point.y - std::cos(site_1.angle) * line_length_,
            },
            site_1.angle
    };

    if (should_draw) {
        render.AddLine(site_1.point, site_2.point);
    }

    nodes_stack.pop();
    nodes_stack.push(site_2);
}

void Drawer::turn_node(bool direction) {
    auto val = (std::numbers::pi * rotation_angle_) / 180.;
    if (direction) { // right
        nodes_stack.top().angle += val;
    } else { // left
        nodes_stack.top().angle -= val;
    }
}

void Drawer::Draw(Renderer &render) {
    nodes_stack.emplace(glm::dvec2{0., 0.}, 0.);
    for (char command_letter: l_system_) {
        // See README.md with a commands list
        switch (command_letter) {
            case 'F':
                move_node(render);
                break;
            case 'f':
                move_node(render, false);
                break;
            case '+':
                turn_node(false);
                break;
            case '-':
                turn_node(true);
                break;
            case '[':
                nodes_stack.push(nodes_stack.top());
                break;
            case ']':
                nodes_stack.pop();
                break;
            default:
                break;
        }
    }
}
