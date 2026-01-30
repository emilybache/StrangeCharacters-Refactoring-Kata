#include "Character.hpp"
#include "CharacterFinder.hpp"
#include "CharacterFactory.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <algorithm>

namespace Characters::Test {

bool contains_character(const std::vector<Character*>& characters, const Character& character) {
    return std::any_of(characters.begin(), characters.end(), [&character](const Character* c) {
        return *c == character;
    });
}

bool are_equivalent(std::vector<Character*> actual, std::vector<Character> expected) {
    if (actual.size() != expected.size()) return false;
    for (const auto& exp : expected) {
        if (!contains_character(actual, exp)) return false;
    }
    return true;
}

TEST(CharacterFinderTest, FindCharacterByFirstName)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto character = finder.FindByFirstName("Jim");
    ASSERT_TRUE(character.has_value());
    ASSERT_EQ("Jim", (*character)->FirstName);
}

TEST(CharacterFinderTest, FindElevenByLastName)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    std::optional<std::string> nullString = std::nullopt;
    auto characters = finder.FindFamilyByLastName(nullString);
    ASSERT_TRUE(contains_character(characters, Character("Eleven")));
}

TEST(CharacterFinderTest, FindParent)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto parent = finder.FindParent("Nancy");
    ASSERT_TRUE(parent.has_value());
    ASSERT_EQ("Karen", (*parent)->FirstName);
}

TEST(CharacterFinderTest, FindNoParent)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto parent = finder.FindParent("George");
    ASSERT_FALSE(parent.has_value());
}

TEST(CharacterFinderTest, FindMonsters)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto monsters = finder.FindMonsters();
    std::vector<Character> expected = {
        Character("Mindflayer"),
        Character("Demagorgon"),
        Character("Demadog"),
        Character("MrWhatsit")
    };
    ASSERT_TRUE(are_equivalent(monsters, expected));
}

TEST(CharacterFinderTest, FindFamily)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto family = finder.FindFamilyByCharacter("Jim");
    std::vector<Character> expected = {
        Character("Eleven")
    };
    ASSERT_TRUE(are_equivalent(family, expected));
}

TEST(CharacterFinderTest, FindFamilyByLastName)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto family = finder.FindFamilyByLastName("Wheeler");
    std::vector<Character> expected = {
        Character("Nancy", "Wheeler"),
        Character("Mike", "Wheeler"),
        Character("Karen", "Wheeler"),
        Character("Holly", "Wheeler")
    };
    ASSERT_TRUE(are_equivalent(family, expected));
}

TEST(CharacterFinderTest, FindNothingByName)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto character = finder.FindByFirstName("George");
    ASSERT_FALSE(character.has_value());
}

TEST(CharacterFinderTest, FindNoFamily)
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto characters = finder.FindFamilyByCharacter("George");
    ASSERT_TRUE(characters.empty());
}

}
