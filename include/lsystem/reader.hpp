//
// Created by one_eyed_john on 24/05/23.
//

#ifndef L_SYSTEMS_READER_HPP
#define L_SYSTEMS_READER_HPP

#include <string>
#include <map>

struct Reader {
    using Rule = std::pair<char, std::string>;

    std::vector<Rule> vector_rules_;
    std::string axiom_;
    int num_gen_ = 0;

    int width_ = 500;
    int height_ = 500;

    void ReadFromConsole();
    void ReadFromFile(const std::string &filename);
};

#endif //L_SYSTEMS_READER_HPP
