#ifndef STRANGECHARACTERS_REFACTORING_KATA_CHARACTERFINDER_HPP
#define STRANGECHARACTERS_REFACTORING_KATA_CHARACTERFINDER_HPP

#include <vector>
#include <memory>
#include <string_view>
#include <optional>
#include <string>

namespace Characters {

class Character;

class CharacterFinder
{
private:
    std::vector<std::shared_ptr<Character>> _allCharacters;

public:
    CharacterFinder(std::vector<std::shared_ptr<Character>> allCharacters);
    std::optional<Character*> FindByFirstName(std::string_view name);
    std::optional<Character*> FindParent(std::string_view firstName);
    std::vector<Character*> FindMonsters();
    std::vector<Character*> FindFamilyByCharacter(std::string_view firstName);
    std::vector<Character*> FindFamilyByLastName(std::optional<std::string> lastName);
};

}

#endif