//
// Created by one_eyed_john on 26/04/23.
//

#include <iostream>

#include <lsystem/lsystem.hpp>
#include <lsystem/drawer.hpp>
#include <lsystem/renderer.hpp>

int main() {
    auto l_system = LSystem("F+F+F+F", {
            {'F', "F+F-F-FF+F+F-F"}
    }, 2);

    // auto renderer = Renderer(600, 600);
    auto drawer = Drawer();

    drawer.SetLSystem(l_system);
    drawer.SetRotationAngle(20.f);
    drawer.SetLineLength(2);

    // drawer.Draw(renderer);
    // renderer.Runtime();

    l_system.SetNumberGenerations(3);
    std::cout << l_system.GetString();

    return 0;
}
