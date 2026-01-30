#include "CharacterFinder.hpp"
#include "Character.hpp"
#include <algorithm>

namespace Characters {
    CharacterFinder::CharacterFinder(std::vector<std::shared_ptr<Character> > allCharacters)
        : _allCharacters(std::move(allCharacters)) {
    }

    std::optional<Character *> CharacterFinder::FindByFirstName(std::string_view name) {
        auto iterator = std::find_if(_allCharacters.begin(), _allCharacters.end(), [&](const auto &character) {
            return character->FirstName == name;
        });
        if (iterator != _allCharacters.end()) {
            Character *character = iterator->get();
            return character;
        } else {
            return std::nullopt;
        }
    }

    std::optional<Character *> CharacterFinder::FindParent(std::string_view firstName) {
        auto child = FindByFirstName(firstName);
        if (not child) {
            return std::nullopt;
        }
        auto parent = *((*child)->parents.begin());
        return parent;
    }

    std::vector<Character *> CharacterFinder::FindMonsters() {
        std::vector<Character *> monsters;
        for (auto &character: _allCharacters) {
            if (character->IsMonster)
                monsters.push_back(character.get());
        }
        return monsters;
    }

    std::vector<Character *> CharacterFinder::FindFamilyByCharacter(std::string_view firstName) {
        auto person = FindByFirstName(firstName);
        if (not person) {
            return {};
        }
        std::set<Character *> family;
        family.insert((*person)->parents.begin(), (*person)->parents.end());
        family.insert((*person)->children.begin(), (*person)->children.end());
        family.insert((*person)->siblings.begin(), (*person)->siblings.end());
        
        return std::vector<Character *>(family.begin(), family.end());
    }

    std::vector<Character *> CharacterFinder::FindFamilyByLastName(std::optional<std::string> lastName) {
        std::vector<Character *> family;
        for (auto &character: _allCharacters) {
            if (character->LastName == lastName
                and not character->IsMonster
            )
                family.push_back(character.get());
        }

        return family;
    }
}
