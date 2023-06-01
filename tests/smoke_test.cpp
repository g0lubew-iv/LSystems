//
// Created by one_eyed_john on 26/04/23.
//

#include <lsystem/lsystem.hpp>
#include <lsystem/renderer.hpp>

int main() {

//    Reader r;
//    r.ReadFromFile();
//
//    auto l_system = LSystem(r.axiom, r.rules, r.numGen);

    // auto drawer = Drawer(l_system.GetString(), r.lineLength, r.rotationAngle);
    auto renderer = Renderer(600, 600);
    // drawer.Draw(renderer);
    renderer.AddLine(glm::vec2{0, 0}, glm::vec2{300, 300});
    renderer.Runtime();

    return 0;
}
