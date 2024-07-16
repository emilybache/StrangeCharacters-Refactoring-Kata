<?php

declare(strict_types=1);

namespace StrangeCharacters;
class Character
{
    public readonly string $firstName;
    public readonly ?string $lastName;
    public readonly bool $isMonster;

    private Character $nemesis;

    private array $children = [];
    private array $parents = [];
    private array $siblings = [];

    private function __construct(string $firstName, ?string $lastName, bool $isMonster) {
        $this->firstName = $firstName;
        $this->lastName = $lastName;
        $this->isMonster = $isMonster;
    }

    public static function withName(string $firstName): Character {
        return new self($firstName, null, false);
    }

    public static function withNameAndMonsterStatus(string $firstName, bool $isMonster): Character {
        return new self($firstName, null, $isMonster);
    }

    public static function withFirstAndLastName(string $firstName, string $lastName): Character {
        return new self($firstName, $lastName, false);
    }

    public function addChild(Character $child): void {
        $this->children[] = $child;
        $child->parents[] = $this;
        foreach ($child->siblings as $sibling) {
            if ($child->firstName !== $sibling->firstName) {
                $child->siblings[] = $sibling;
                $this->siblings[] = $child;
            }
        }
    }

    public function getNemesis(): Character
    {
        return $this->nemesis;
    }

    public function setNemesis(Character $nemesis): void
    {
        $this->nemesis = $nemesis;
    }

    public function __toString(): string {
        return sprintf("Character(%s, %s, %s)", $this->firstName, $this->firstName, $this->firstName ? "True" : "False");
    }

    public function getParents(): array
    {
        return $this->parents;
    }

    public function getChildren(): array
    {
        return $this->children;
    }

    public function getSiblings(): array
    {
        return $this->siblings;
    }
}