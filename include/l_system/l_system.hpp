//
// Created by one_eyed_john on 26/04/23.
//

#ifndef L_SYSTEMS_L_SYSTEM_HPP
#define L_SYSTEMS_L_SYSTEM_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <boost/algorithm/string/find_format.hpp>

/**
 * \brief A class for LSystem, contains rules, axiom and number of generations
 */
class LSystem {
public:
    /// @brief rules_container contains 2 elements: name of variable over which
    /// it will be performed and formula itself
    /// E. g. rule (FF_F[+FF][-FF]F[-F][+F]F) equals <"FF", "F[+FF][-FF]F[-F][+F]F">
    using rules_container = std::unordered_map<std::string, std::string>;

private:
    /// @brief Axiom of LSystem: it can include any letters and special symbols
    /// E. g:  axiom = VZFFF
    std::string axiom_;

    /// @brief Rules container
    /// * E. g: V->[+++W][---W]YV
    rules_container rules{};

    /// @brief In fact, it's a number of iterations of the rules
    int num_gen = 0;

    /// @brief What LSystem outputs; depends on axiom (initially equal to it), rules and number of generations
    std::string res;

    /// @brief Calculate res_ variable; called in method GetString()
    void generate();

public:
    /**
     * \brief LSystem is uniquely determined by an axiom and rules.
     * If number of generations is 0, we have LSystem equals axiom; this is default option
     * \param[in] axiom
     * \param[in] map_rules
     * \param[in] number_generations
     */
    LSystem(const std::string &axiom, rules_container map_rules, int number_generations);

    ~LSystem() = default;

    /**
     * \brief Annul previous generations and generate new (what depends on new number of generations)
     * \return res_
     */
    std::string GetString();
};

/**
 * \brief A class for generating LSystem's string (method LSystem::GetString());
 * realize function find(), searches for matches in the range. See boost::find_format_all
 */
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

/**
 * \brief A class for generating LSystem's string (method LSystem::GetString());
 * realize function replace(), formats matches in the range. See boost::find_format_all
 */
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

#endif //L_SYSTEMS_L_SYSTEM_HPP
