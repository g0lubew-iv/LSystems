#include <l_system/reader.hpp>
#include <l_system/l_system.hpp>
#include <l_system/drawer.hpp>
#include <l_system/renderer.hpp>

int WIDTH = 500;
int HEIGHT = 500;

int main(int argc, char **argv) {
    auto reader = Reader();
    reader.width = WIDTH;
    reader.height = HEIGHT;

    if (reader.ParseCommandLine(argc, argv)) {
        return 0;
    }

    // reader.ParseFile("/home/one_eyed_john/dev/c_projects/l_systems/input.txt");

    auto l_system = LSystem(reader.axiom, reader.rules, reader.numGen);
    auto drawer = Drawer(l_system.GetString(), reader.lineLength, reader.rotationAngle);
    auto renderer = Renderer();
    drawer.Draw(renderer);
    renderer.UpdateData();

    renderer.Runtime();

    return 0;
}