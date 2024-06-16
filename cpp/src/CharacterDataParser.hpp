#ifndef STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_HPP
#define STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_HPP

#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

#include "Character.hpp"

class CharacterFinder;

namespace Characters {
    class CharacterDataParser {
    public:

        static void probably_initializeFromFile_andstuff(const std::string& filename);
        static std::optional<Character*> evaluatePath(const std::string& path);
    private:
        static void applesauce(nlohmann::basic_json<> data);
        static std::vector<std::shared_ptr<Character>> allCharacters;
        static std::optional<Character*> findCharacter(std::vector<std::shared_ptr<Character>>, std::string_view firstName);
    };

}
#endif //STRANGECHARACTERS_REFACTORING_KATA_CHARACTERPARSER_HPP
