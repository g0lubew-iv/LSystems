//
// Created by one_eyed_john on 24/05/23.
//

#include <lsystem/reader.hpp>

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

void Reader::ReadFromConsole() {
    std::cout << "Enter size of window (pixels): ";
    std::cin >> width_ >> height_;

    if ((width_ <= 0) || (height_ <= 0)) {
        throw std::invalid_argument("Width and height_ must be non-negative!");
    }

    std::cout << "Enter number of generations: ";
    std::cin >> num_gen_;

    if (num_gen_ < 0) {
        throw std::invalid_argument("Number of generation must be non-negative!");
    }

    std::cout << "Enter axiom_: ";
    std::cin >> axiom_;

    std::cout << "Enter rules:\n";
    while (!std::cin.eof()) {
        std::string rule;
        std::getline(std::cin, rule);
        std::string new_rule;
        for (int i = 0; i < rule.length(); i++) {
            char letter = rule[i];
            if ((letter == ' ') || (letter == '>') || ((letter == '-') && (rule[i + 1] == '>'))) {
                continue;
            }
            new_rule += letter;
        }

        rule = "";
        for (int i = 1; i < rule.length(); i++) {
            rule += new_rule[i];
        }

        vector_rules_.emplace_back(new_rule[0], rule);
    }
}

// TODO: reading from file
void Reader::ReadFromFile(const std::string &filename) {
    std::string line;
    std::cout << std::filesystem::current_path() << "\n";
    std::ifstream file(filename);

    if (file.is_open()) {
        while (getline(file, line)) {
            std::cout << line << '\n';
        }
        file.close();
    } else {
        std::cout << "Failed to open file " << filename << "!\n";
    }
}