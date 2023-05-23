//
// Created by one_eyed_john on 26/04/23.
//

#include <lsystem/lsystem.hpp>
#include <vector>

LSystem::LSystem(const std::string &axiom, std::initializer_list<Rule> list_rules, unsigned int number_generations)
        : axiom_(axiom), res_(axiom) {

    for (const auto &rule: list_rules) {
        char name = rule.first;
        std::string rule_sense = rule.second;

        if (rules_.find(name) != rules_.end()) {
            rules_.find(name)->second = rule_sense;
        } else {
            rules_.insert(LSystem::Rule(name, rule_sense));
        }
    }

    SetNumberGenerations(number_generations);
}

void LSystem::SetNumberGenerations(unsigned int num_gen) {
    num_gen_ = num_gen;
}

void LSystem::generate() {
    for (int i = 0; i < num_gen_; i++) {
        std::vector<size_t> position_vector;
        for (const auto &rule: rules_) {

            unsigned int shift = 0; // offset by the length of rule
            char name = rule.first;
            std::string rule_sense = rule.second;
            size_t position = res_.find(name, 0); // first encounter of element in string

            while (position != std::string::npos) {
                // While we have this name of rule in res_
                position_vector.push_back(position);
                position = res_.find(name, position + 1);
            }

            // std::sort(position_vector.begin(), position_vector.end()); non-useful, but it can help for debug

            for (unsigned long j: position_vector) {
                res_.replace(j + shift, 1, rule_sense);
                shift += rule_sense.length() - 1;
            }
        }
    }
}

std::string LSystem::GetString() {
    res_ = axiom_; // annul previous generations!
    generate();
    return res_;
}
