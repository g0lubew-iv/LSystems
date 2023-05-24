//
// Created by one_eyed_john on 26/04/23.
//

#ifndef L_SYSTEMS_LSYSTEM_HPP
#define L_SYSTEMS_LSYSTEM_HPP

#include <string>
#include <vector>
#include <map>

/**
 * \brief A class for LSystem, contains rules, axiom_ and number of generations
 * \param axiom
 * \param list_rules
 * \param number_generations
 */
class LSystem {
public:
    /// @brief Rule contains 2 elements: name of variable over which
    /// it will be performed and formula itself
    /// E. g. rule (F -> F[+FF][-FF]F[-F][+F]F) equals <'F', "F[+FF][-FF]F[-F][+F]F">
    using Rule = std::pair<char, std::string>;

private:
    /// @brief Axiom of LSystem: it can include any letters and special symbols
    /// E. g:  axiom_ = VZFFF
    std::string axiom_;
    /**
     * \brief Rules container
     * E. g: V -> [+++W][---W]YV
     * W -> +X[-W]Z
     * X -> -W[+X]Z
     * Y -> YZ
     * Z -> [-FFF][+FFF]F
     */
    std::map<char, std::string> rules_ = {};

    /// @brief In fact, it's a number of iterations of the rules
    /// num_gen is unsigned, so it's non-negative
    unsigned int num_gen_ = 0;

    /// @brief What LSystem outputs; depends on axiom_ (initially equal to it), rules and number of generations
    std::string res_;

    /// @brief Calculate res_ variable; called in method GetString()
    void generate();

public:
    /**
     * \brief LSystem is uniquely determined by an axiom_ and rules.
     * If number of generations is 0, we have LSystem equals axiom_; this is default option
     * \param[in] axiom
     * \param[in] list_rules
     * \param[in] number_generations
     */
    LSystem(const std::string &axiom, std::initializer_list<Rule> list_rules, unsigned int number_generations);

    /// @brief The same as LSystem constructor for std::initializer_list<Rule>
    LSystem(const std::string &axiom, const std::vector<Rule> &vector_rules, unsigned int number_generations);

    ~LSystem() = default;

    LSystem(const LSystem &other) = default;

    LSystem &operator=(const LSystem &other) = default;

    LSystem(LSystem &&other) noexcept = default;

    LSystem &operator=(LSystem &&other) noexcept = default;

    /**
     * \brief Change number of generations: the volume of res_ variable will change accordingly
     * \param[in] num_gen
     */
    void SetNumberGenerations(unsigned int num_gen);

    /**
     * \brief Annul previous generations and generate new (what depends on new number of generations)
     * \return res_
     */
    std::string GetString();
};

#endif //L_SYSTEMS_LSYSTEM_HPP
