//
// Created by one_eyed_john on 24/05/23.
//

#include <lsystem/reader.hpp>

#include <iostream>
#include <string>
#include <fstream>

void Reader::ReadFromConsole() {
    std::cout << "Enter size of window (pixels): ";
    std::cin >> width_ >> height_;

    if ((width_ <= 0) || (height_ <= 0)) {
        // Check if window parameters are positive, rectangle must be non-degenerate
        throw std::invalid_argument("Width and height_ must be positive!");
    }

    std::cout << "Enter number of generations: ";
    std::cin >> num_gen_;

    if (num_gen_ < 0) {
        // Check if number of generations is non-negative, then cast to unsigned int
        throw std::invalid_argument("Number of generation must be non-negative!");
    }

    std::cout << "Enter axiom_: ";
    std::cin >> axiom_;

    std::cout << "Enter rules:\n";
    while (!std::cin.eof()) {
        std::string rule;
        std::getline(std::cin, rule); // reading from stream
        std::string new_rule; // rule without unuseful symbols

        for (int i = 0; i < rule.length(); i++) {
            char letter = rule[i];
            if ((letter == ' ') || (letter == '>') || ((letter == '-') && (rule[i + 1] == '>'))) {
                // Syntax of rules: Variable -> Rule body
                continue;
            }
            new_rule += letter;
        }

        rule = ""; // too lazy to create new local variable
        for (int i = 1; i < new_rule.length(); i++) {
            // just copying all elements starting from second (index 1)
            rule += new_rule[i];
        }

        if (new_rule.length() > 1) {
            vector_rules_.emplace_back(new_rule[0], rule);
        }
        // else we have an empty (consisting of a service symbol) string, it's definitely non-rule
    }
}

void Reader::ReadFromFile() {
    std::cout << "Enter absolute path to file: ";
    std::string file_path;
    std::cin >> file_path;

    std::string line;
    std::ifstream file(file_path);

    bool is_axiom = true; // the first line after number of generations

    if (file.is_open()) {

        file >> width_ >> height_;

        if ((width_ <= 0) || (height_ <= 0)) {
            // Check if window parameters are positive, rectangle must be non-degenerate
            throw std::invalid_argument("Width and height_ must be positive!");
        }

        file >> num_gen_;

        if (num_gen_ < 0) {
            // Check if number of generations is non-negative, then cast to unsigned int
            throw std::invalid_argument("Number of generation must be non-negative!");
        }

        getline(file, line); // and if the empty string is here, we will get rid of it

        while (getline(file, line)) {
            if (is_axiom) {
                axiom_ = line;
                is_axiom = false;
            } else {
                std::string new_rule; // rule without unuseful symbols

                for (int i = 0; i < line.length(); i++) {
                    char letter = line[i];
                    if ((letter == ' ') || (letter == '>') || ((letter == '-') && (line[i + 1] == '>'))) {
                        // Syntax of rules: Variable -> Rule body
                        continue;
                    }
                    new_rule += letter;
                }

                line = ""; // too lazy to create new local variable
                for (int i = 1; i < new_rule.length(); i++) {
                    // just copying all elements starting from second (index 1)
                    line += new_rule[i];
                }

                if (new_rule.length() > 1) {
                    vector_rules_.emplace_back(new_rule[0], line);
                }
                // else we have an empty (consisting of a service symbol) string, it's definitely non-rule
            }
        }
        file.close();
    } else {
        std::cout << "Failed to open file " << file_path << "!\n";
    }
}