#ifndef STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_HPP
#define STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_HPP

#include <string>
#include <vector>
#include <memory>

#include "Character.hpp"

namespace Characters {
    class CharacterParser {
    public:
        static void initializeFromFile(const std::string& filename);
        static std::optional<Character*> evaluatePath(const std::string& path);
    private:
        static std::vector<std::unique_ptr<Character>> allCharacters;
        static std::optional<Character*> findCharacter(std::string_view firstName);
        static std::optional<Character*> findCharacterWithFamily(std::vector<Character*> filteredCharacters, std::string_view tempPathWithoutCurlyBraces);
        static std::vector<Character*> filterCharactersByFamilyName(std::string_view familyName, std::string_view characterName);
    };

}
#endif //STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_HPP
