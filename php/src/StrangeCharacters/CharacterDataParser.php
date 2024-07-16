<?php

declare(strict_types=1);

namespace StrangeCharacters;

class CharacterDataParser
{
    private static array $allCharacters = [];
    private static CharacterFinder $characterFinder;

    public static function probably_InitializeFromFile_AndStuff(?string $filename): void
    {
        if ($filename == null) {
            $filename = ROOT_DIR . DIRECTORY_SEPARATOR . "resources" . DIRECTORY_SEPARATOR . "strange_characters.json";
        }

        self::$allCharacters = self::applesauce(json_decode(file_get_contents($filename), false));
        self::$characterFinder = new CharacterFinder(self::$allCharacters);
    }

    private static function applesauce(array $data): array
    {
        $result = [];
        foreach ($data as $characterData) {
            $result[] = Character::withFirstAndLastNameAndMonsterStatus($characterData->FirstName, $characterData->LastName, $characterData->IsMonster);
        }

        foreach ($data as $characterData) {
            // find nemesis
            if (!empty($characterData->Nemesis)) {
                $nemesis = self::findCharacter($characterData->Nemesis, $result);
                $character = self::findCharacter($characterData->FirstName, $result);
                $character->setNemesis($nemesis);
            }

            // add family
            if (!empty($characterData->Children)) {
                $character = self::findCharacter($characterData->FirstName, $result);
                foreach ($characterData->Children as $childName) {
                    $child = self::findCharacter($childName, $result);
                    if ($child != null)
                        $character->addChild($child);
                }
            }
        }

        return $result;
    }

    private static function findCharacter(string $name, array $result): ?Character
    {
        return current(array_filter($result, function (Character $character) use ($name) {
            return $character->firstName === $name;
        }));
    }

    public static function evaluatePath(string $path): ?Character
    {
        $character = null;

        $hasFamilyName = false;
        $characterName = "";
        $familyName = "";
        $tempPathWithoutCurlyBraces = "";
        $curlyBraces = "";
        $structureList = explode("/", $path);
        for ($i = count($structureList) - 1; $i >= 0; $i--) {
            if (empty($structureList[$i]))
                continue;
            $localName = "";
            $familyLocalNameList = explode(":", $structureList[$i]);
            if (count($familyLocalNameList) == 2) {
                if (!$hasFamilyName) {
                    $hasFamilyName = true;
                }

                $familyName = $familyLocalNameList[0];
                $localName = $familyLocalNameList[1];
            } else if (count($familyLocalNameList) == 1) {
                $localName = $familyLocalNameList[0];
            }

            if ($i == count($structureList) - 1) {
                $characterName = $localName;
            }

            $localNameWithoutCurlyBraces = preg_replace("|\{[^{]*?}|", "", $localName);
            $pattern = "|(.*)\{([^{]*)}|";
            $matches = [];
            preg_match($pattern, $localName, $matches);
            if (count($matches) > 0) {
                $curlyBraces = $matches[2];
                $characterName = $matches[1];
            }

            $tempPathWithoutCurlyBraces = "/" . $localNameWithoutCurlyBraces . $tempPathWithoutCurlyBraces;
        }

        if (!$hasFamilyName) {
            $character = self::$characterFinder->findByFirstName($characterName);
            if ($curlyBraces == "Nemesis") {
                return $character->getNemesis();
            }

            return $character;
        }

        $filteredCharacters = self::$characterFinder->findFamilyByLastName($familyName);
        if (!empty($filteredCharacters)) {
            $names = array_filter(explode("/", $tempPathWithoutCurlyBraces), fn(string $name) => !empty($name));
            if (count($names) == 2) {
                $firstName = next($names);
                $candidates = array_filter($filteredCharacters, fn(Character $c) => ($c->firstName == $firstName));
                $character = !empty($candidates) ? current($candidates) : null;
            }
            if ($character != null && $curlyBraces == "Nemesis") {

                return $character->getNemesis();
            }
        }

        return $character;
    }
}