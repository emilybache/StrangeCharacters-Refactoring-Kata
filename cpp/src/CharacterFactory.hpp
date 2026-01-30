#ifndef STRANGECHARACTERS_REFACTORING_KATA_CHARACTERFACTORY_H
#define STRANGECHARACTERS_REFACTORING_KATA_CHARACTERFACTORY_H

#include "Character.hpp"
#include <vector>
#include <memory>

namespace Characters {

class CharacterFactory {
public:
    static std::vector<std::shared_ptr<Character>> StrangeCharacters();
    static std::vector<std::shared_ptr<Character>> WheelerFamily();
};

}

#endif //STRANGECHARACTERS_REFACTORING_KATA_CHARACTERFACTORY_H