//
// Created by one_eyed_john on 24/05/23.
//

#ifndef L_SYSTEMS_READER_HPP
#define L_SYSTEMS_READER_HPP

#include <filesystem>
#include <unordered_map>

/**
 * \brief A struct for reading data for LSystems in two ways: from arguments of command line or file,
 * and then passing them to LSystem constructor
 */
struct Reader {
    /// @brief rules_container contains 2 elements: name of variable over which
    /// it will be performed and formula itself
    /// E. g. rule (FF_F[+FF][-FF]F[-F][+F]F) equals <"FF", "F[+FF][-FF]F[-F][+F]F">
    using rules_container = std::unordered_map<std::string, std::string>;

    /// @brief A container with rules
    rules_container rules;

    /// @brief An axiom of LSystem
    std::string axiom;

    /// @brief A number of generations; default it is 0, axiom
    int numGen = 0;

    /// @brief Parameters of window
    int width = 500;
    int height = 500;

    /// @brief Length of the drawing system (command 'F')
    double lineLength = 50.;

    /// @brief Angle of rotation (see commands '+' and '-')
    double rotationAngle = 90.;

    /**
     * \brief Checking if NumGen is non-negative (>= 0)
     */
    void CheckNumGen() const {
        if (numGen < 0)
            // Check if number of generations is non-negative, then cast to unsigned int
            throw std::invalid_argument("Number of generation must be non-negative!");
    }

    /**
     * \brief Reading and editing data based on command line arguments;
     * syntax of rules: Variable_Rule
     */
    bool ParseCommandLine(int ac, char *av[]);

    /**
     * \brief Reading and editing data from file with rules; syntax of rules: Variable->Rule;
     * N. B: new rule is written from new line, you have to give absolute path to file
     */
    void ParseFile(const std::string &file_path);
};

#endif //L_SYSTEMS_READER_HPP
