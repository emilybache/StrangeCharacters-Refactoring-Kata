#include "doctest/doctest.h"

#include "CharacterParser.hpp"

namespace Characters::Test {

    TEST_CASE("CharacterParser") {
        CharacterParser::initializeFromFile("../../strange_characters.json");
        SUBCASE("Find with empty path") {
            auto character = CharacterParser::evaluatePath("");
            REQUIRE(character.has_value() == false);
        }
        SUBCASE("Find by Path") {
            auto character = CharacterParser::evaluatePath("/Jim/Eleven");
            REQUIRE("Eleven" == character.value()->FirstName);
        }
        SUBCASE("Find by family name") {
            auto character = CharacterParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy");
            REQUIRE("Nancy" == character.value()->FirstName);
        }
        SUBCASE("Find nemesis") {
            auto character = CharacterParser::evaluatePath("/Joyce/Will{Nemesis}");
            REQUIRE("Mindflayer" == character.value()->FirstName);
        }
        SUBCASE("Find nemesis with family name") {
            auto character = CharacterParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
            REQUIRE(character.has_value() == false);
        }
        SUBCASE("Find nothing family name") {
            auto character = CharacterParser::evaluatePath("/Wheeler:Karen/Wheeler:George");
            REQUIRE(character.has_value() == false);
        }
    }


}

