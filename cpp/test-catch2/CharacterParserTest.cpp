#include <catch2/catch.hpp>

#include "CharacterDataParser.hpp"

namespace Characters::Test {

    TEST_CASE("CharacterParser") {
        CharacterDataParser::probably_initializeFromFile_andstuff("../../strange_characters.json");
        SECTION("Find with empty path") {
            auto character = CharacterDataParser::evaluatePath("");
            REQUIRE(character.has_value() == false);
        }
        SECTION("Find by Path") {
            auto character = CharacterDataParser::evaluatePath("/Jim/Eleven");
            REQUIRE("Eleven" == character.value()->FirstName);
        }
        SECTION("Find by family name") {
            auto character = CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy");
            REQUIRE("Nancy" == character.value()->FirstName);
        }
        SECTION("Find nemesis") {
            auto character = CharacterDataParser::evaluatePath("/Joyce/Will{Nemesis}");
            REQUIRE("Mindflayer" == character.value()->FirstName);
        }
        SECTION("Find nemesis with family name") {
            auto character = CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
            REQUIRE(character.has_value() == false);
        }
        SECTION("Find nothing family name") {
            auto character = CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:George");
            REQUIRE(character.has_value() == false);
        }
    }


}
