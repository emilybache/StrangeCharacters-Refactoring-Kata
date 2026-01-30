#include "CharacterFactory.hpp"

namespace Characters {

std::vector<std::shared_ptr<Character>> CharacterFactory::StrangeCharacters() {
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
    auto holly = std::make_shared<Character>("Holly", "Wheeler");
    auto steve = std::make_shared<Character>("Steve", "Harrington");
    auto mindflayer = std::make_shared<Character>("Mindflayer", std::nullopt, true);
    auto demagorgon = std::make_shared<Character>("Demagorgon", std::nullopt, true);
    auto demadog = std::make_shared<Character>("Demadog", std::nullopt, true);
    auto mrwhatsit = std::make_shared<Character>("MrWhatsit", std::nullopt, true);

    joyce->AddChild(jonathan.get());
    joyce->AddChild(will.get());
    jim->AddChild(eleven.get());
    karen->AddChild(nancy.get());
    karen->AddChild(mike.get());
    karen->AddChild(holly.get());

    eleven->SetNemesis(demagorgon.get());
    will->SetNemesis(mindflayer.get());
    dustin->SetNemesis(demadog.get());
    holly->SetNemesis(mrwhatsit.get());

    return {
            joyce,
            jim,
            mike,
            will,
            eleven,
            dustin,
            lucas,
            nancy,
            jonathan,
            mindflayer,
            demagorgon,
            demadog,
            karen,
            holly,
            steve,
            mrwhatsit
    };
}

std::vector<std::shared_ptr<Character>> CharacterFactory::WheelerFamily() {
    auto karen = std::make_shared<Character>("Karen", "Wheeler");
    auto mike = std::make_shared<Character>("Mike", "Wheeler");
    auto nancy = std::make_shared<Character>("Nancy", "Wheeler");
    auto holly = std::make_shared<Character>("Holly", "Wheeler");

    karen->AddChild(nancy.get());
    karen->AddChild(mike.get());
    karen->AddChild(holly.get());

    return {
            karen,
            mike,
            nancy,
            holly
    };
}

}
