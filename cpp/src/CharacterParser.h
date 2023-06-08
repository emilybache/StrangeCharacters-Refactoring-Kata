

#ifndef STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_H
#define STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_H

#include <string>
#include <vector>

#include "Character.hpp"

using namespace std;

namespace Characters {
    class CharacterParser {
    public:
        static void initializeFromFile(const string &filename);

    private:
        std::vector<std::unique_ptr<Character>> allCharacters;
    };

}
#endif //STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_H
