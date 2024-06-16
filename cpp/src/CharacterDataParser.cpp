#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

#include "CharacterDataParser.hpp"
#include "CharacterFinder.hpp"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

namespace {
    std::vector<std::string> split(std::string s, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
        {
            if (!token.empty())
                tokens.push_back(token);
        }
        return tokens;
    }
}

namespace Characters {
    std::vector<std::shared_ptr<Character>> CharacterDataParser::allCharacters;
    
    void CharacterDataParser::probably_initializeFromFile_andstuff(const std::string &filename) {
        allCharacters.clear();

        std::ifstream data_stream(filename, std::ifstream::in);
        if (!data_stream.is_open()) {
            std::cout << "Error opening file:" << filename << '\n';
            std::cout << "Error: " << strerror(errno) << '\n';
            return;
        }
        auto data = json::parse(data_stream);
        applesauce(data);
    }

    void CharacterDataParser::applesauce(nlohmann::basic_json<> data) {
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
                auto nemesis = findCharacter(allCharacters, characterData["Nemesis"].get<std::string>());
                auto character = findCharacter(allCharacters, characterData["FirstName"].get<std::string>());

                if (character.has_value())
                    (*character)->SetNemesis(nemesis);
            }

            if (!characterData["Children"].is_null())
            {
                auto character = findCharacter(allCharacters, characterData["FirstName"].get<std::string>());
                for (auto childName : characterData["Children"])
                {
                    auto child = findCharacter(allCharacters, childName.get<std::string>());
                    if (child.has_value())
                        (*character)->AddChild(*child);
                }
            }
        }
    }

    std::optional<Character *> CharacterDataParser::evaluatePath(const std::string &path) {
        std::optional<Character*> character = std::nullopt;
        CharacterFinder characterFinder(allCharacters);

        auto hasFamilyName = false;
        auto characterName = std::string();
        auto familyName = std::string();
        auto tempPathWithoutCurlyBraces = std::string();
        auto curlyBraces = std::string();

        auto structureList = split(path, '/');

        for (int i = structureList.size() - 1; i >= 0; --i)
        {
            auto localName = std::string();
            auto localNameWithoutCurlyBraces = std::string();
            auto familyLocalNameList = split(structureList[i], ':');
            if (familyLocalNameList.size() == 2)
            {
                if (!hasFamilyName)
                {
                    familyName = familyLocalNameList[0];
                    hasFamilyName = true;
                }

                familyName = familyLocalNameList[0];
                localName = familyLocalNameList[1];
            }
            else if (familyLocalNameList.size() == 1)
            {
                localName = familyLocalNameList[0];
            }

            if (i == structureList.size() - 1)
            {
                characterName = localName;
            }

            localNameWithoutCurlyBraces = std::regex_replace(localName, std::regex("\\{[^{]*?\\}"), "");

            auto matches = std::smatch { };

            if (std::regex_match(localName, matches, std::regex("(.*)\\{([^{]*)\\}")))
            {
                curlyBraces = matches[2];
                characterName = matches[1];
            }

            tempPathWithoutCurlyBraces = tempPathWithoutCurlyBraces.insert(0, "/" + localNameWithoutCurlyBraces);
        }

        if (!hasFamilyName)
        {
            character = findCharacter(allCharacters, characterName);
            if (curlyBraces == "Nemesis")
            {
                return (*character)->Nemesis;
            }
            return character;
        }

        auto filteredCharacters = characterFinder.FindFamilyByLastName(familyName);
        if (!filteredCharacters.empty())
        {
            auto firstName = std::string_view(tempPathWithoutCurlyBraces).substr(
                std::string_view(tempPathWithoutCurlyBraces).find_last_of("/")+1
            );
            auto c = std::find_if(filteredCharacters.begin(), filteredCharacters.end(),
                                  [&firstName](const auto& character) { return character->FirstName == firstName; });
            if (c != filteredCharacters.end()) {
                character = *c;
            } else {
                character = std::nullopt;
            }
        
            if (character != nullptr && curlyBraces == "Nemesis")
            {
                return (*character)->Nemesis;
            }
        }

        return character;
    }

    std::optional<Character*> CharacterDataParser::findCharacter(std::vector<std::shared_ptr<Character>> characters, std::string_view firstName) {
        auto c = std::find_if(characters.begin(), characters.end(),
                [&firstName](const auto& character) { return character->FirstName == firstName; });

        if (c != characters.end())
            return c->get();
        return std::nullopt;
    }
}
