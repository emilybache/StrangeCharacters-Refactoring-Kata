<?php

declare(strict_types=1);

namespace StrangeCharacters;

class CharacterFactory
{
    public static function allTestData(): array
    {
        $joyce = Character::withFirstAndLastName("Joyce", "Byers");
        $jim = Character::withFirstAndLastName("Jim", "Hopper");
        $mike = Character::withFirstAndLastName("Mike", "Wheeler");
        $eleven = Character::withName("Eleven");
        $dustin = Character::withFirstAndLastName("Dustin", "Henderson");
        $lucas = Character::withFirstAndLastName("Lucas", "Sinclair");
        $nancy = Character::withFirstAndLastName("Nancy", "Wheeler");
        $jonathan = Character::withFirstAndLastName("Jonathan", "Byers");
        $will = Character::withFirstAndLastName("Will", "Byers");
        $karen = Character::withFirstAndLastName("Karen", "Wheeler");
        $steve = Character::withFirstAndLastName("Steve", "Harrington");
        $mindflayer = Character::withNameAndMonsterStatus("Mindflayer", true);
        $demagorgon = Character::withNameAndMonsterStatus("Demagorgon", true);
        $demadog = Character::withNameAndMonsterStatus("Demadog", true);

        $joyce->addChild($jonathan);
        $joyce->addChild($will);
        $jim->addChild($eleven);
        $karen->addChild($nancy);
        $karen->addChild($mike);

        $eleven->setNemesis($demagorgon);
        $will->setNemesis($mindflayer);
        $dustin->setNemesis($demadog);

        return [
                $joyce,
                $jim,
                $mike,
                $will,
                $eleven,
                $dustin,
                $lucas,
                $nancy,
                $jonathan,
                $mindflayer,
                $demagorgon,
                $demadog,
                $karen,
                $steve];
    }

    public static function wheelerFamily(): array {
        $karen = Character::withFirstAndLastName("Karen", "Wheeler");
        $mike =  Character::withFirstAndLastName("Mike", "Wheeler");
        $nancy = Character::withFirstAndLastName("Nancy", "Wheeler");

        $karen->addChild($nancy);
        $karen->addChild($mike);

        return [$karen, $mike, $nancy];
    }
}