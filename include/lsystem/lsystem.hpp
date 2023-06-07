//
// Created by one_eyed_john on 26/04/23.
//

#ifndef L_SYSTEMS_LSYSTEM_HPP
#define L_SYSTEMS_LSYSTEM_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string/find_format.hpp>

/**
 * \brief A class for LSystem, contains rules, axiom and number of generations
 * \param axiom
 * \param list_rules
 * \param number_generations
 */
class LSystem {
public:
    /// @brief rule_type contains 2 elements: name of variable over which
    /// it will be performed and formula itself
    /// E. g. rule (F -> F[+FF][-FF]F[-F][+F]F) equals <'F', "F[+FF][-FF]F[-F][+F]F">
    using rules_container = std::unordered_map<std::string, std::string>;

private:
    /// @brief Axiom of LSystem: it can include any letters and special symbols
    /// E. g:  axiom = VZFFF
    std::string axiom_;
    /**
     * \brief Rules container
     * E. g: V -> [+++W][---W]YV
     * W -> +X[-W]Z
     * X -> -W[+X]Z
     * Y -> YZ
     * Z -> [-FFF][+FFF]F
     */
    rules_container rules{};

    /// @brief In fact, it's a number of iterations of the rules
    /// numGen is unsigned, so it's non-negative
    unsigned int num_gen = 0;

    /// @brief What LSystem outputs; depends on axiom (initially equal to it), rules and number of generations
    std::string res;

    /// @brief Calculate res_ variable; called in method GetString()
    void generate();

public:
    /**
     * \brief LSystem is uniquely determined by an axiom and rules.
     * If number of generations is 0, we have LSystem equals axiom; this is default option
     * \param[in] axiom
     * \param[in] list_rules
     * \param[in] number_generations
     */
    LSystem(const std::string &axiom, rules_container vector_rules, unsigned int number_generations);

    ~LSystem() = default;

    LSystem(const LSystem &other) = default;

    LSystem &operator=(const LSystem &other) = default;

    LSystem(LSystem &&other) noexcept = default;

    LSystem &operator=(LSystem &&other) noexcept = default;

    /**
     * \brief Annul previous generations and generate new (what depends on new number of generations)
     * \return res_
     */
    std::string GetString();
};

class finder_type {
public:
    explicit finder_type(LSystem::rules_container &rules) : rules_(rules) {}

    ~finder_type() = default;

    template<class iterator_type>
    boost::iterator_range<iterator_type> operator()(iterator_type begin, iterator_type end) {
        for (auto &it = begin; it != end; ++it) {
            for (auto &rule: rules_) {
                auto length = static_cast<int>(rule.first.size());
                if (abs(std::distance(it, end)) >= length) {
                    if (std::string_view(it, it + length) == rule.first) {
                        return {it, it + length};
                    }
                } else {
                    continue;
                }
            }
        }
        return {end, end};
    }

private:
    LSystem::rules_container &rules_;
};

class formatter_type {
public:
    explicit formatter_type(LSystem::rules_container &rules) : rules_(rules) {}

    ~formatter_type() = default;

    template<class iterator_type>
    boost::iterator_range<iterator_type> operator()(const boost::iterator_range<iterator_type> &range) const {
        auto it = rules_.find(std::string(std::begin(range), std::end(range)));
        return {it->second};
    }

private:
    LSystem::rules_container &rules_;
};

#endif //L_SYSTEMS_LSYSTEM_HPP
