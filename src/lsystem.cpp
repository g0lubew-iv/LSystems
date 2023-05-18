//
// Created by one_eyed_john on 26/04/23.
//
#include <random>
#include <lsystem/lsystem.hpp>

LSystem::LSystem(const std::vector<char> &variables, const std::vector<char> &constants,
                 const std::string &ax, const std::vector<Rule> &rs) :
        vars_(variables), cons_(constants),
        axiom_(ax), rules_(rs) {
    ;
}

bool LSystem::check_rules() {
    int sum = 0;
    for (const auto &rule: rules_) {
        sum += rule.probability_;
    }
    return sum == 1;
}

int get_random_number_from_0_to_1() {
    using u32 = uint_least32_t;
    using engine = std::mt19937;
    std::random_device os_seed;
    const u32 seed = os_seed();

    engine generator(seed);
    std::uniform_int_distribution<u32> distribute(0, 1);

    return static_cast<int>(distribute(generator));
}

std::string LSystem::rule_out() {
    if (check_rules()) {
        int random_number = get_random_number_from_0_to_1();
        int sum = 0;

        for (const auto &rule: rules_) {
            sum += rule.probability_;
            if (random_number < sum) {
                return rule.to_;
            }
        }

    }

    throw std::exception();
}

std::istream &LSystem::readFrom(std::istream &istrm) {

}

std::ostream &LSystem::writeTo(std::ostream &ostrm) const {

}
