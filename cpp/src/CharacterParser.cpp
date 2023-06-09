#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>

#include "CharacterParser.h"
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
        std::optional<Character*> character = std::nullopt;

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
            character = findCharacter(characterName);
            if (curlyBraces == "Nemesis")
            {
                return (*character)->Nemesis;
            }
            return character;
        }

        auto filteredCharacters = filterCharactersByFamilyName(familyName, characterName);
        if (!filteredCharacters.empty())
        {
            character = findCharacterWithFamily(filteredCharacters, tempPathWithoutCurlyBraces);
            if (curlyBraces == "Nemesis")
            {
                return (*character)->Nemesis;
            }
        }

        return character;
    }

    std::optional<Character*> CharacterParser::findCharacter(std::string_view firstName) {
        auto c = std::find_if(allCharacters.begin(), allCharacters.end(),
                [&firstName](const auto& character) { return character->FirstName == firstName; });

        if (c != allCharacters.end())
            return c->get();
        return std::nullopt;
    }

    std::optional<Character*> CharacterParser::findCharacterWithFamily(std::vector<Character *> filteredCharacters,
                                                                   std::string_view tempPathWithoutCurlyBraces) {
        auto firstName = tempPathWithoutCurlyBraces.substr(
                tempPathWithoutCurlyBraces.find_last_of("/")+1
                );

        auto c = std::find_if(filteredCharacters.begin(), filteredCharacters.end(),
                              [&firstName](const auto& character) { return character->FirstName == firstName; });
        if (c != filteredCharacters.end())
            return *c;

        return std::nullopt;
    }

    std::vector<Character *>
    CharacterParser::filterCharactersByFamilyName(std::string_view familyName, std::string_view characterName) {
        auto found = std::vector<Character*> { };
        for (auto c = allCharacters.begin(); c != allCharacters.end(); ++c)
            if ((*c)->LastName == familyName)
                found.push_back(c->get());

        if (std::any_of(found.begin(), found.end(),
                [&characterName](const auto& character) { return character->FirstName == characterName; }))
        {
            return found;
        }

        return std::vector<Character*> { };
    }
}