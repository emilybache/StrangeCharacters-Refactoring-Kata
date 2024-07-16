<?php

declare(strict_types=1);


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
        self::assertEquals(array_values($finder->findFamilyByLastName(null)), [Character::withName("Eleven")]);
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
        self::assertEquals([
            Character::withName("Mindflayer"),
            Character::withName("Demagorgon"),
            Character::withName("Demadog")
        ], array_values($finder->findMonsters()));
    }

    #[Test]
    public function FindFamily(): void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        $family = $finder->findFamilyByCharacter("Jim");
        self::assertEquals([
            Character::withName("Eleven")
        ], array_values($family));
    }

    #[Test]
    public function FindFamilyByLastName(): void {
        $finder = new CharacterFinder(CharacterFactory::allTestData());
        $family = $finder->findFamilyByLastName("Wheeler");
        self::assertEquals([
            Character::withFirstAndLastName("Mike", "Wheeler"),
            Character::withFirstAndLastName("Nancy", "Wheeler"),
            Character::withFirstAndLastName("Karen", "Wheeler")
        ], array_values($family));
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

    // private static List<String> firstNames(List<Character> characters) {
    //     return characters.stream().map(f -> f.firstName).toList();
    // }
}
