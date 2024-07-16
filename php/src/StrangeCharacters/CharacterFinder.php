<?php

declare(strict_types=1);

namespace StrangeCharacters;

readonly class CharacterFinder
{
    private array $allCharacters;

    public function __construct(array $allCharacters)
    {
        $this->allCharacters = $allCharacters;
    }

    public function findByFirstName(string $characterName): ?Character
    {
        $found = array_filter($this->allCharacters, fn(Character $c) => $c->firstName == $characterName);

        return !empty($found) ? current($found) : null;
    }

    public function findParent(string $firstName): ?Character
    {
        $child = $this->findByFirstName($firstName);
        if ($child == null) {
            return null;
        }

        return current($child->getParents()) ?? null;
    }

    public function findFamilyByLastName(?string $lastName): array
    {
        $family = array_filter($this->allCharacters, fn(Character $c) => $c->lastName != null &&
                $c->lastName == $lastName || ($lastName == null));

        return $lastName == null ? array_filter($family, fn(Character $c) => !$c->isMonster) : $family;
    }

    public function findMonsters(): array
    {
        return array_filter($this->allCharacters, fn(Character $c) => $c->isMonster);
    }

    public function findFamilyByCharacter(string $firstName): array
    {
        $person = $this->findByFirstName($firstName);
        if ($person == null) {
            return [];
        }

        return $person->getParents() + $person->getChildren() + $person->getSiblings();
    }
}