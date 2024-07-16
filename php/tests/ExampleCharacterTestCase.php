<?php

declare(strict_types=1);

use PHPUnit\Framework\TestCase;
use PHPUnit\Framework\Attributes\Test;
use StrangeCharacters\Character;
use StrangeCharacters\CharacterFactory;

class ExampleCharacterTestCase extends TestCase
{
    #[Test]
    public function oneCharacterTests(): void {
        // Arrange
        $nancy = Character::withFirstAndLastName("Nancy", "Wheeler");

        // No Act step - we will just illustrate some assertions you can do on a Character

        // Assert
        self::assertEquals("Nancy", $nancy->firstName);
        // This assertion works because Character implements "equals"
        self::assertEquals(Character::withFirstAndLastName("Nancy", "Wheeler"), $nancy);
    }

     #[Test]
     public function characterListTests() : void{
         // Arrange
         $charactersList = CharacterFactory::wheelerFamily();

         // No Act step - we will just illustrate some assertions you can do on a List of Characters

         // Assert
         self::assertNotNull($charactersList);
         self::assertCount(3, $charactersList);
         self::assertContains(Character::withFirstAndLastName("Nancy", "Wheeler"), $charactersList);
         self::assertEquals([
                 Character::withFirstAndLastName("Karen", "Wheeler"),
                 Character::withFirstAndLastName("Mike", "Wheeler"),
                 Character::withFirstAndLastName("Nancy", "Wheeler")
         ], array_values($charactersList));
         self::assertEquals([
                 "Karen Wheeler",
                 "Mike Wheeler",
                 "Nancy Wheeler"
         ], array_map(fn(Character $character) => $character->firstName. " " .$character->lastName,$charactersList));
     }
}
