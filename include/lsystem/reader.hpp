//
// Created by one_eyed_john on 24/05/23.
//

#ifndef L_SYSTEMS_READER_HPP
#define L_SYSTEMS_READER_HPP

#include <string>
#include <vector>

/**
 * \brief A class for reading data for LSystems in two ways: from console or file,
 * and then passing them to LSystem constructor
 */
struct Reader {

    /// @brief Rule contains 2 elements: name of variable over which
    /// it will be performed and formula itself
    /// E. g. rule (F -> F[+FF][-FF]F[-F][+F]F) equals <'F', "F[+FF][-FF]F[-F][+F]F">
    using Rule = std::pair<char, std::string>;

    /// @brief A container with rules
    std::vector<Rule> vector_rules_;

    /// @brief An axiom of LSystem
    std::string axiom_;

    /// @brief A number of generations
    int num_gen_ = 0;

    /// @brief Parameters of window
    int width_ = 500;
    int height_ = 500;

    /**
     * \brief Reading and editing data from console input; syntax of rules: Variable -> Rule body
     */
    void ReadFromConsole();

    /**
     * \brief Reading and editing data from file with rules; syntax of rules: Variable -> Rule body;
     * N. B: new rule is written from new line, you have to give absolute path to file
     */
    void ReadFromFile();
};

#endif //L_SYSTEMS_READER_HPP
