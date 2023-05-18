//
// Created by one_eyed_john on 26/04/23.
//

#include <lsystem/lsystem.hpp>

int main() {
    std::vector<char> vars = {'0', '1'};
    std::vector<char> cons = {};
    std::string axiom = "0";
    std::vector<LSystem::Rule> rules = {
            LSystem::Rule{"1", "11"},
            LSystem::Rule{"0", "1A0"},
    };

    LSystem system{vars, cons, axiom, rules};

    return 0;
}
