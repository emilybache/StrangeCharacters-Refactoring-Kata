#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "CharacterParser.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace Characters {
    std::vector<std::unique_ptr<Character>> CharacterParser::allCharacters;

    void CharacterParser::initializeFromFile(const std::string &filename) {
        std::ifstream data_stream(filename, std::ifstream::in);
        if (!data_stream.is_open()) {
            std::cout << "Error opening file:" << filename << '\n';
            std::cout << "Error: " << strerror(errno) << '\n';
            return;
        }
        auto data = json::parse(data_stream);
        for (auto characterData : data)
        {
            auto character = new Character(
                characterData["FirstName"].get<std::string>(),
                characterData["LastName"].is_string() ?
                    characterData["LastName"].get<std::string>() : std::string(),
                characterData["IsMonster"].get<bool>()
            );
            allCharacters.emplace_back(character);
        }

        for (auto characterData : data)
        {
            if (!characterData["Nemesis"].is_null())
            {
                auto nemesis = findCharacter(characterData["Nemesis"].get<std::string>());
                auto character = findCharacter(characterData["FirstName"].get<std::string>());

                if (character.has_value())
                    (*character)->SetNemesis(nemesis);
            }

            if (!characterData["Children"].is_null())
            {
                auto character = findCharacter(characterData["FirstName"].get<std::string>());
                for (auto childName : characterData["Children"])
                {
                    auto child = findCharacter(childName.get<std::string>());
                    if (child.has_value())
                        (*character)->AddChild(*child);
                }
            }
        }
    }

    std::optional<Character *> CharacterParser::evaluatePath(const std::string &path) {
        return std::nullopt;
    }

    std::optional<Character*> CharacterParser::findCharacter(std::string_view firstName) {
        auto c = std::find_if(allCharacters.begin(), allCharacters.end(),
                [&](const auto& character) { return character->FirstName == firstName; });

        if (c != allCharacters.end())
            return c->get();
        return std::nullopt;
    }

    std::optional<Character*> CharacterParser::findCharacterWithFamily(std::vector<Character *> filteredCharacters,
                                                                   std::string_view tempPathWithoutCurlyBraces) {

        return std::nullopt;
    }

    std::vector<Character *>
    CharacterParser::filterCharactersByFamilyName(std::string_view familyName, std::string_view characterName) {
    }
}