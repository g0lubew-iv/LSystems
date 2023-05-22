//
// Created by one_eyed_john on 26/04/23.
//

#include <lsystem/lsystem.hpp>
#include <vector>

void LSystem::SetAxiom(const std::string &axiom) {
    this->axiom_ = axiom;
    res_ = axiom;
}

void LSystem::AddRule(char name, const std::string& rule) {
    if (rules_.find(name) == rules_.end()) {
        rules_.insert(std::pair<char, std::string>(name, rule));
    }
    else {
        rules_.find(name)->second = rule;
    }
}

void LSystem::SetNumberGenerations(unsigned int count) {
    num_gen_ = count;
}

void LSystem::generate() {
    for (int i = 0; i < num_gen_; i++) {
        unsigned int offset = 0;
        std::vector<size_t> position;

        for (auto begin = rules_.begin(); begin != rules_.end(); begin++) {
            char sign = begin->first;
            size_t pos = res_.find(sign, 0);

            while (pos != std::string::npos) {
                position.push_back(pos);
                pos = res_.find(sign, pos + 1);
            }

            for (unsigned long j : position) {
                std::string rule = rules_.find(sign)->second;
                res_.replace(j + offset, 1, rule);
                offset += rule.length() - 1;
            }
        }
    }
}

std::string LSystem::GetString() {
    generate();
    return res_;
}
