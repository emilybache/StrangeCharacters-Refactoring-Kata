

#ifndef STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_H
#define STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_H

#include <string>
#include <vector>
#include <memory>

#include "Character.hpp"

using namespace std;

namespace Characters {
    class CharacterParser {
    public:
        static void initializeFromFile(const string& filename);
        static optional<Character*> evaluatePath(const string& path);
    private:
        static vector<std::unique_ptr<Character>> allCharacters;
        static optional<Character*> findCharacter(string_view firstName);
        static optional<Character*> findCharacterWithFamily(vector<Character*> filteredCharacters, string_view tempPathWithoutCurlyBraces);
        static vector<Character*> filterCharactersByFamilyName(string_view familyName, string_view characterName);
    };

}
#endif //STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_H
