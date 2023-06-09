#include <lsystem/reader.hpp>
#include <lsystem/lsystem.hpp>
#include <lsystem/drawer.hpp>
#include <lsystem/renderer.hpp>

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