
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "CharacterParser.h"

namespace Characters::Test {


    TEST(CharacterParserTest, EmptyPath) {
        CharacterParser::initializeFromFile("../../strange_characters.json");
        auto character = CharacterParser::evaluatePath("");
        ASSERT_EQ(character.has_value(), false);
    }

    TEST(CharacterParserTest, NormalPath) {
        CharacterParser::initializeFromFile("../../strange_characters.json");
        auto character = CharacterParser::evaluatePath("/Jim/Eleven");
        ASSERT_EQ("Eleven", character.value()->FirstName);
    }

    TEST(CharacterParserTest, FamilyName) {
        CharacterParser::initializeFromFile("../../strange_characters.json");
        auto character = CharacterParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy");
        ASSERT_EQ("Nancy", character.value()->FirstName);
    }

    TEST(CharacterParserTest, Nemesis) {
        CharacterParser::initializeFromFile("../../strange_characters.json");
        auto character = CharacterParser::evaluatePath("/Joyce/Will{Nemesis}");
        ASSERT_EQ("Mindflayer", character.value()->FirstName);
    }

    TEST(CharacterParserTest, NemesisWithFamily) {
        CharacterParser::initializeFromFile("../../strange_characters.json");
        auto character = CharacterParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
        ASSERT_EQ(character.has_value(), false);
    }

    TEST(CharacterParserTest, MissingFamily) {
        CharacterParser::initializeFromFile("../../strange_characters.json");
        auto character = CharacterParser::evaluatePath("/Wheeler:Karen/Wheeler:George");
        ASSERT_EQ(character.has_value(), false);
    }

}
