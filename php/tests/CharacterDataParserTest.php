<?php

declare(strict_types=1);

use PHPUnit\Framework\Attributes\Test;
use PHPUnit\Framework\TestCase;
use StrangeCharacters\CharacterDataParser;

class CharacterDataParserTest extends TestCase
{
    #[Test]
    public function findCharacterByPath(): void
    {
        CharacterDataParser::probably_InitializeFromFile_AndStuff(null);
        self::assertEquals("Eleven", CharacterDataParser::evaluatePath("/Jim/Eleven")->firstName);
    }

    #[Test]
    public function findCharacterByEmptyPath(): void
    {
        CharacterDataParser::probably_InitializeFromFile_AndStuff(null);
        self::assertNull(CharacterDataParser::evaluatePath(""));
    }

    #[Test]
    public function FindCharacterByPathWithFamilyName(): void
    {
        CharacterDataParser::probably_InitializeFromFile_AndStuff(null);
        self::assertEquals("Nancy", CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy")->firstName);
    }

    #[Test]
    public function FindNemesisByPath(): void
    {
        CharacterDataParser::probably_InitializeFromFile_AndStuff(null);
        self::assertEquals("Mindflayer", CharacterDataParser::evaluatePath("/Joyce/Will{Nemesis}")->firstName);
    }

    #[Test]
    public function FindNemesisByPathAndFamilyName(): void
    {
        CharacterDataParser::probably_InitializeFromFile_AndStuff(null);
        self::assertNull(CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}"));
    }

    #[Test]
    public function FindNothingByPathAndFamilyName(): void
    {
        CharacterDataParser::probably_InitializeFromFile_AndStuff(null);
        self::assertNull(CharacterDataParser::evaluatePath("/Wheeler:Karen/Wheeler:George"));
    }
}
