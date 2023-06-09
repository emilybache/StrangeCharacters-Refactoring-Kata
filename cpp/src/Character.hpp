#ifndef STRANGECHARACTERS_REFACTORING_KATA_CHARACTER_HPP
#define STRANGECHARACTERS_REFACTORING_KATA_CHARACTER_HPP

#include <optional>
#include <string>
#include <set>

namespace Characters {

class Character
{
public:
    const std::string FirstName;
    const std::optional<std::string> LastName;
    const bool IsMonster;

    std::optional<Character*> Nemesis;

    std::set<Character*> children;
    std::set<Character*> siblings;
    std::set<Character*> parents;

    Character(std::string firstName, std::optional<std::string> lastName = std::nullopt, bool isMonster = false);
    void AddChild(Character* child);
    void SetNemesis(std::optional<Character*> monster);
    friend std::string to_string(const Character& character);
    bool operator==(const Character& other) const;
};

}

#endif