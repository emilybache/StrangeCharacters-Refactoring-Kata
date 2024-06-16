
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "CharacterDataParser.hpp"

namespace Characters::Test {


    TEST(CharacterParserTest, EmptyPath) {
        CharacterDataParser::probably_initializeFromFile_andstuff("../../strange_characters.json");
        auto character = CharacterDataParser::evaluatePath("");
        ASSERT_EQ(character.has_value(), false);
    }

    TEST(CharacterParserTest, NormalPath) {
        CharacterDataParser::probably_initializeFromFile_andstuff("../../strange_characters.json");
        auto character = CharacterDataParser::evaluatePath("/Jim/Eleven");
        ASSERT_EQ("Eleven", character.value()->FirstName);
    }

    TEST(CharacterParserTest, FamilyName) {
        CharacterDataParser::probably_initializeFromFile_andstuff("../../strange_characters.json");
        auto character = CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy");
        ASSERT_EQ("Nancy", character.value()->FirstName);
    }

    TEST(CharacterParserTest, Nemesis) {
        CharacterDataParser::probably_initializeFromFile_andstuff("../../strange_characters.json");
        auto character = CharacterDataParser::evaluatePath("/Joyce/Will{Nemesis}");
        ASSERT_EQ("Mindflayer", character.value()->FirstName);
    }

    TEST(CharacterParserTest, NemesisWithFamily) {
        CharacterDataParser::probably_initializeFromFile_andstuff("../../strange_characters.json");
        auto character = CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
        ASSERT_EQ(character.has_value(), false);
    }

    TEST(CharacterParserTest, MissingFamily) {
        CharacterDataParser::probably_initializeFromFile_andstuff("../../strange_characters.json");
        auto character = CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:George");
        ASSERT_EQ(character.has_value(), false);
    }

}
