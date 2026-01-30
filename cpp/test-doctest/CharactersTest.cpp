#include "Character.hpp"
#include "CharacterFactory.hpp"
#include "CharacterFinder.hpp"

#include "doctest/doctest.h"

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

TEST_CASE("Find Character By First Name")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto character = finder.FindByFirstName("Jim");
    REQUIRE(character.has_value());
    REQUIRE("Jim" == (*character)->FirstName);
}

TEST_CASE("Find Eleven By Last Name")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    std::optional<std::string> nullString = std::nullopt;
    auto characters = finder.FindFamilyByLastName(nullString);
    REQUIRE(contains_character(characters, Character("Eleven")));
}

TEST_CASE("Find Parent")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto parent = finder.FindParent("Nancy");
    REQUIRE(parent.has_value());
    REQUIRE("Karen" == (*parent)->FirstName);
}

TEST_CASE("Find No Parent")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto parent = finder.FindParent("George");
    REQUIRE(!parent.has_value());
}

TEST_CASE("Find Monsters")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto monsters = finder.FindMonsters();
    std::vector<Character> expected = {
        Character("Mindflayer"),
        Character("Demagorgon"),
        Character("Demadog"),
        Character("MrWhatsit")
    };
    REQUIRE(are_equivalent(monsters, expected));
}

TEST_CASE("Find Family")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto family = finder.FindFamilyByCharacter("Jim");
    std::vector<Character> expected = {
        Character("Eleven")
    };
    REQUIRE(are_equivalent(family, expected));
}

TEST_CASE("Find Family By Last Name")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto family = finder.FindFamilyByLastName("Wheeler");
    std::vector<Character> expected = {
        Character("Nancy", "Wheeler"),
        Character("Mike", "Wheeler"),
        Character("Karen", "Wheeler"),
        Character("Holly", "Wheeler")
    };
    REQUIRE(are_equivalent(family, expected));
}

TEST_CASE("Find Nothing By Name")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto character = finder.FindByFirstName("George");
    REQUIRE(!character.has_value());
}

TEST_CASE("Find No Family")
{
    CharacterFinder finder(CharacterFactory::StrangeCharacters());
    auto characters = finder.FindFamilyByCharacter("George");
    REQUIRE(characters.empty());
}

}
