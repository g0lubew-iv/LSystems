//
// Created by one_eyed_john on 24/05/23.
//

#include <lsystem/reader.hpp>

#include <iostream>
#include <fstream>

void Reader::ReadFromConsole() {
    std::cout << "Enter size of window (pixels): ";
    std::cin >> width >> height;

    if ((width <= 0) || (height <= 0)) {
        // Check if window parameters are positive, rectangle must be non-degenerate
        throw std::invalid_argument("Width and height must be positive!");
    }

    std::cout << "Enter number of generations: ";
    std::cin >> numGen;

    if (numGen < 0) {
        // Check if number of generations is non-negative, then cast to unsigned int
        throw std::invalid_argument("Number of generation must be non-negative!");
    }

    std::cout << "Enter axiom: ";
    std::cin >> axiom;

    std::cout << "Enter rules:\n";
    while (!std::cin.eof()) {
        std::string rule;
        std::getline(std::cin, rule); // reading from stream
        std::string new_rule; // rule without unuseful symbols

        for (int i = 0; i < rule.length(); i++) {
            char letter = rule[i];
            if ((letter == ' ') || (letter == '>') || ((letter == '-') && (rule[i + 1] == '>'))) {
                // Syntax of rules: Variable -> rule_type body
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
            rules.emplace_back(new_rule[0], rule);
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

    file >> width >> height;

    if ((width <= 0) || (height <= 0)) {
        // Check if window parameters are positive, rectangle must be non-degenerate
        throw std::invalid_argument("Width and height must be positive!");
    }

    file >> numGen;
    file >> lineLength >> rotationAngle;

    if (numGen < 0) {
        // Check if number of generations is non-negative, then cast to unsigned int
        throw std::invalid_argument("Number of generation must be non-negative!");
    }

    std::getline(file, line);
    std::getline(file, axiom);

    while (std::getline(file, line)) {
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
            rules.emplace_back(new_rule[0], line);
        }
        // else we have an empty (consisting of a service symbol) string, it's definitely non-rule
    }
}