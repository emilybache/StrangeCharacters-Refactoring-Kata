
#include <iostream>
#include <string>
#include <fstream>

#include "CharacterParser.h"
#include "nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

void Characters::CharacterParser::initializeFromFile(const string& filename) {

    std::ifstream data_stream(filename, ifstream::in);
    if ( ! data_stream.is_open())
    {
        std::cout << "Error opening file:" << filename << '\n';
        std::cout << "Error: " << strerror(errno) << '\n';
    }
    nlohmann::json result;
    data_stream >> result;

}
