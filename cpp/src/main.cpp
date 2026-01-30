#include <iostream>
#include <string>
#include "CharacterDataParser.hpp"
#include "Character.hpp"

int main(int argc, char* argv[]) {
    std::string filename = "strange_characters.json";
    if (argc > 1) {
        filename = argv[1];
        std::cout << "Using character file: " << filename << std::endl;
    }

    Characters::CharacterDataParser::probably_initializeFromFile_andstuff(filename);

    while (true) {
        std::cout << "Please enter the path to evaluate: (type 'exit' to exit program)" << std::endl;

        std::string path;
        if (!std::getline(std::cin, path) || path == "exit") {
            break;
        }

        auto character_opt = Characters::CharacterDataParser::evaluatePath(path);

        if (character_opt) {
            std::cout << "Character: " << to_string(**character_opt) << std::endl;
        } else {
            std::cout << "Character: null" << std::endl;
        }
    }

    return 0;
}
