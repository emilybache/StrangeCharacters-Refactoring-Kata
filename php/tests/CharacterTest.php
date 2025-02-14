<?php

declare(strict_types=1);

namespace StrangeCharacters\Tests;

use StrangeCharacters\Character;
use PHPUnit\Framework\TestCase;
use StrangeCharacters\CharacterFactory;
use StrangeCharacters\CharacterFinder;
use PHPUnit\Framework\Attributes\Test;

class CharacterTest extends TestCase
{
    #[Test]
    public function findCharacterByFirstName(): void {
        self::assertEquals("Jim", (new CharacterFinder(CharacterFactory::allTestData()))->findByFirstName("Jim")->firstName);
    }

    #[Test]
    public function FindElevenByLastName(): void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        $family = $finder->findFamilyByLastName(null);
        self::assertEquals("Eleven", current($family)->firstName);
    }

    #[Test]
    public function FindParent():  void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        $parent = $finder->findParent("Nancy");
        self::assertEquals("Karen", $parent->firstName);
    }

    #[Test]
    public function FindNoParent() : void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        self::assertNull($finder->findParent("George"));
    }

    #[Test]
    public function FindMonsters() :  void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        $foundMonsters = array_map(fn(Character $character) => $character->firstName, $finder->findMonsters());
        foreach([
            "Mindflayer",
            "Demagorgon",
            "Demadog"
        ] as $monsterName) {
            self::assertContains($monsterName, $foundMonsters);
        }
    }

    #[Test]
    public function FindFamily(): void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        $family = $finder->findFamilyByCharacter("Jim");
        self::assertContains("Eleven", array_map(fn(Character $character) => $character->firstName, $family));
        self::assertCount(1, $family);
    }

    #[Test]
    public function FindFamilyByLastName(): void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        $familyNames = array_map(fn(Character $character) => [$character->firstName, $character->lastName], $finder->findFamilyByLastName("Wheeler"));
        foreach ( [
            ["Mike", "Wheeler"],
            ["Nancy", "Wheeler"],
            ["Karen", "Wheeler"]
                  ] as $names) {
            self::assertContains($names, $familyNames);
        }
        self::assertCount(3, $familyNames);
    }

    #[Test]
    public function FindNothingByName(): void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        self::assertNull($finder->findByFirstName("George$"));
    }

    #[Test]
    public function FindNoFamily(): void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        $characters = $finder->findFamilyByCharacter("George");
        self::assertCount(0, $characters);
    }
}
