#include "Character.hpp"
#include "CharacterFinder.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

namespace Characters::Test {

std::vector<std::shared_ptr<Character>> allTestData()
{
    auto joyce = std::make_shared<Character>("Joyce", "Byers");
    auto jim = std::make_shared<Character>("Jim", "Hopper");
    auto mike = std::make_shared<Character>("Mike", "Wheeler");
    auto eleven = std::make_shared<Character>("Eleven");
    auto dustin = std::make_shared<Character>("Dustin", "Henderson");
    auto lucas = std::make_shared<Character>("Lucas", "Sinclair");
    auto nancy = std::make_shared<Character>("Nancy", "Wheeler");
    auto jonathan = std::make_shared<Character>("Jonathan", "Byers");
    auto will = std::make_shared<Character>("Will", "Byers");
    auto karen = std::make_shared<Character>("Karen", "Wheeler");
    auto steve = std::make_shared<Character>("Steve", "Harrington");
    auto mindflayer = std::make_shared<Character>("Mindflayer", std::nullopt, true);
    auto demagorgon = std::make_shared<Character>("Demagorgon", std::nullopt, true);
    auto demadog = std::make_shared<Character>("Demadog", std::nullopt, true);
    
    joyce->AddChild(jonathan.get());
    joyce->AddChild(will.get());
    jim->AddChild(eleven.get());
    karen->AddChild(nancy.get());
    karen->AddChild(mike.get());
    
    eleven->Nemesis = demagorgon.get();
    will->Nemesis = mindflayer.get();
    dustin->Nemesis = demadog.get();

    std::vector<std::shared_ptr<Character>> characters;
    for (auto& i : { &joyce, &jim, &mike, &eleven, &dustin, &lucas, &nancy, &jonathan, &will, &karen, &steve, &mindflayer, &demagorgon, &demadog }) {
      characters.push_back(std::move(*i));
    }

    return characters;
}

TEST(CharacterFinderTest, FindCharacterByFirstName)
{
    CharacterFinder finder(allTestData());
    auto character = finder.FindByFirstName("Jim");
    ASSERT_EQ("Jim", (*character)->FirstName);
}

}
