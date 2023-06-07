#include <lsystem/reader.hpp>
#include <lsystem/lsystem.hpp>
#include <lsystem/drawer.hpp>
#include <lsystem/renderer.hpp>

int main() {
    auto reader = Reader();
    reader.ReadFromFile();
    auto l_system = LSystem(reader.axiom, reader.rules, reader.numGen);
    auto drawer = Drawer(l_system.GetString(), reader.lineLength, reader.rotationAngle);
    auto renderer = Renderer();
    drawer.Draw(renderer);
    renderer.UpdateData();

    renderer.Runtime();

    return 0;
}