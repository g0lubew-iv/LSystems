//
// Created by one_eyed_john on 26/04/23.
//

#include <lsystem/lsystem.hpp>
#include <lsystem/drawer.hpp>
#include <lsystem/renderer.hpp>
#include <lsystem/reader.hpp>

#include <iostream>

int main() {

    Reader r;
    r.ReadFromConsole();

//    auto l_system = LSystem("F+F+F+F", {
//            {'F', "F+F-F-FF+F+F-F"}
//    }, 2);

    // Vector to initializer_list (yet in the Reader?)
    LSystem l_system = LSystem(r.axiom_, r.vector_rules_, r.num_gen_);

    auto renderer = Renderer(r.width_, r.height_);
    auto drawer = Drawer(l_system.GetString());

    drawer.SetLineLength(2);

    drawer.Draw(renderer);
    renderer.Runtime();

    return 0;
}
