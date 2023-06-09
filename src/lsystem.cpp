//
// Created by one_eyed_john on 26/04/23.
//

#include <lsystem/lsystem.hpp>
#include <utility>

LSystem::LSystem(const std::string &axiom, rules_container map_rules, int number_generations)
        : axiom_(axiom), res(axiom), num_gen(number_generations), rules(std::move(map_rules)) {
    ;
}

void LSystem::generate() {
    auto finder = finder_type(rules);
    auto formatter = formatter_type(rules);

    for (unsigned int i = 0; i < num_gen; i++) {
        boost::find_format_all(res, finder, formatter);
    }
}

std::string LSystem::GetString() {
    res = axiom_; // annul previous generations!
    generate();
    return res;
}
