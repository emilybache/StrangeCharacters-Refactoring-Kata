
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "CharacterParser.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

namespace Characters {
    void CharacterParser::initializeFromFile(const string &filename) {

        std::ifstream data_stream(filename, ifstream::in);
        if (!data_stream.is_open()) {
            std::cout << "Error opening file:" << filename << '\n';
            std::cout << "Error: " << strerror(errno) << '\n';
            return;
        }
        nlohmann::json result;
        data_stream >> result;

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