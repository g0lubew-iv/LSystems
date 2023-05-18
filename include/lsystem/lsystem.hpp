//
// Created by one_eyed_john on 26/04/23.
//

#ifndef L_SYSTEMS_LSYSTEM_HPP
#define L_SYSTEMS_LSYSTEM_HPP

#include <sstream>
#include <vector>

class LSystem {
public:
    struct Rule {
        std::string from_;
        std::string to_;
        std::uint8_t probability_{1};
    };

public:
    LSystem() = default;

    LSystem(const std::vector<char> &, const std::vector<char> &, const std::string &, const std::vector<Rule> &);

    std::istream& readFrom(std::istream&);
    std::ostream& writeTo(std::ostream&) const;

private:
    std::string axiom_;
    std::vector<Rule> rules_;
    std::vector<char> vars_;
    std::vector<char> cons_;
    std::uint8_t generation_{0};

private:
    bool check_rules();

    std::string rule_out();
};

inline std::ostream& operator<<(std::ostream& ostrm, const LSystem& rhs) {
    return rhs.writeTo(ostrm);
}

inline std::istream& operator>>(std::istream& istrm, LSystem& rhs) {
    return rhs.readFrom(istrm);
}

#endif //L_SYSTEMS_LSYSTEM_HPP
