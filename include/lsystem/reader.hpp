//
// Created by one_eyed_john on 24/05/23.
//

#ifndef L_SYSTEMS_READER_HPP
#define L_SYSTEMS_READER_HPP

#include <filesystem>
#include <unordered_map>

/**
 * \brief A class for reading data for LSystems in two ways: from console or file,
 * and then passing them to LSystem constructor
 */
struct Reader {
    /// @brief rule_type contains 2 elements: name of variable over which
    /// it will be performed and formula itself
    /// E. g. rule (F -> F[+FF][-FF]F[-F][+F]F) equals <'F', "F[+FF][-FF]F[-F][+F]F">
    using rules_container = std::unordered_map<std::string, std::string>;

    /// @brief A container with rules
    rules_container rules;

    /// @brief An axiom of LSystem
    std::string axiom;

    /// @brief A number of generations
    int numGen = 0;

    /// @brief Parameters of window
    int width = 500;
    int height = 500;

    double lineLength = 10.;
    double rotationAngle = 90.;

    /**
     * \brief Reading and editing data from console input; syntax of rules: Variable -> rule_type body
     */
    // void ReadFromConsole();

    /**
     * \brief Reading and editing data from file with rules; syntax of rules: Variable -> rule_type body;
     * N. B: new rule is written from new line, you have to give absolute path to file
     */
    void ReadFromFile();
};

#endif //L_SYSTEMS_READER_HPP
