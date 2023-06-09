//
// Created by one_eyed_john on 24/05/23.
//

#include <lsystem/reader.hpp>

#include <iostream>
#include <fstream>

bool Reader::ParseCommandLine(int argc, char *argv[]) {
    if (argc == 1) {
        // there are no parameters; e.g. reading from file
        return false;
    }

    bool is_rul = false;
    bool is_axm = false;
    bool is_gen = false;
    bool is_len = false;
    bool is_rot = false;

    // the first argument (argv[0]) is executable filename!
    for (int i = 1; i < argc; i++) {
        bool is_error = false;
        std::string str = static_cast<std::string>(argv[i]);

        if (str == "-rul") {
            is_rul = true;
            continue;
        } else if (str == "-axm") {
            is_axm = true;
            continue;
        } else if (str == "-gen") {
            is_gen = true;
            continue;
        } else if (str == "-len") {
            is_len = true;
            continue;
        } else if (str == "-rot") {
            is_rot = true;
            continue;
        } else if ((str == "-h") || (str == "-help")) {
            std::cout << "-gen : Set a number of generations <integer>\n";
            std::cout << "-len : Set a line length <double>\n";
            std::cout << "-rot : Set a rotation angle <double>\n";
            std::cout << "-axm : Set an axiom <string>\n";
            std::cout << "-rul : Set a new rule <string>_<string>\n";
            return true;
        } else if (is_rul) {
            is_rul = false;
            auto it = str.begin();

            while ((it != str.end()) && (std::string_view(it, it + 2) != "->")) {
                // symbol '->' is separator between variable and rule body
                ++it;
            }
            if (it == str.begin()) {
                continue;
            }
            if (std::distance(it, str.end()) <= 2) {
                // not enough space
                continue;
            }

            rules[std::string(str.begin(), it)] = std::string_view(it + 2, str.end());
        } else if (is_axm) {
            axiom = str;
        } else if (is_gen) {
            numGen = std::stoi(str);
            CheckNumGen(); // is non-negative
        } else if (is_len) {
            lineLength = std::stod(str);
        } else if (is_rot) {
            rotationAngle = std::stod(str);
        } else {
            is_error = true;
        }

        // Cancel all flags: if user enters e.g. "-rot -rul X_FX+X-F",
        // there will be no uncertainty with the angle of rotation
        is_rul = false;
        is_axm = false;
        is_gen = false;
        is_len = false;
        is_rot = false;

        if (is_error) {
            throw std::invalid_argument("Argument " + str + " is not found!");
        }

    }
    return false;
}

void Reader::ParseFile(const std::string &file_path) {
    std::string line;
    std::ifstream file(file_path);

    file >> numGen;
    CheckNumGen();

    file >> lineLength >> rotationAngle;

    std::getline(file, line);
    std::getline(file, axiom);

    while (std::getline(file, line)) {
        auto it = line.begin();
        while ((it != line.end()) && (std::string_view(it, it + 2) != "->")) {
            // symbols "->" are separator between variable and rule body
            ++it;
        }
        if (it == line.begin()) {
            continue;
        }
        if (std::distance(it, line.end()) <= 2) {
            // not enough space
            continue;
        }
        rules[std::string(line.begin(), it)] = std::string_view(it + 2, line.end());
    }
}
