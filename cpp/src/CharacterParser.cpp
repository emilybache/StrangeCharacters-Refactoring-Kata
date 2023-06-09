
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "CharacterParser.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

namespace Characters {
    vector<std::unique_ptr<Character>> CharacterParser::allCharacters;

    void CharacterParser::initializeFromFile(const string &filename) {
        std::ifstream data_stream(filename, ifstream::in);
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

    std::optional<Character *> CharacterParser::evaluatePath(const string &path) {
        return std::nullopt;
    }

    optional<Character *> CharacterParser::findCharacter(string_view firstName) {
        return std::nullopt;
    }

    optional<Character *> CharacterParser::findCharacterWithFamily(vector<Character *> filteredCharacters,
                                                                   string_view tempPathWithoutCurlyBraces) {

        return std::nullopt;
    }

    vector<Character *>
    CharacterParser::filterCharactersByFamilyName(string_view familyName, string_view characterName) {
        return vector<Character *>();
    }
}