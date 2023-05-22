//
// Created by one_eyed_john on 26/04/23.
//

#ifndef L_SYSTEMS_LSYSTEM_HPP
#define L_SYSTEMS_LSYSTEM_HPP

#include <string>
#include <map>

class LSystem {
public:

    LSystem() = default;

    void SetAxiom(const std::string &);

    void AddRule(char, const std::string &);

    void SetNumberGenerations(unsigned int);

    std::string GetString();

private:
    std::string axiom_;
    std::map<char, std::string> rules_ = {};
    unsigned int num_gen_ = 0;
    std::string res_;

    void generate();
};

#endif //L_SYSTEMS_LSYSTEM_HPP
