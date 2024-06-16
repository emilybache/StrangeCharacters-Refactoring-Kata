from dataclasses import dataclass, field
from typing import List, Optional
from typing import TypeVar

Character = TypeVar("Character")


@dataclass
class Character:
    firstName: str
    lastName: str = None
    isMonster: bool = False
    _nemesis: Character = None
    _children: List[Character] = field(default_factory=list)
    _siblings: List[Character] = field(default_factory=list)
    _parents: List[Character] = field(default_factory=list)

    def _add_child(self, child: Character):
        self._children.append(child)
        child._parents.append(self)
        for character in self._children:
            if child.firstName != character.firstName:
                child._siblings.append(character)
                character._siblings.append(child)

    def _set_nemesis(self, monster):
        self._nemesis = monster

    def __eq__(self, __value):
        if not isinstance(__value, Character):
            return False
        return self.firstName.__eq__(__value.firstName)

    def __hash__(self):
        return self.firstName.__hash__()

    def __str__(self):
        return f"Character({self.firstName}, {self.lastName}, isMonster:{self.isMonster})"


class CharacterFinder:
    def __init__(self, allCharacters: List[Character]):
        self._allCharacters = allCharacters

    def find_by_first_name(self, name: str) -> Optional[Character]:
        found = [c for c in self._allCharacters if c.firstName == name]
        return found[0] if found else None

    def find_parent(self, first_name: str) -> Optional[Character]:
        child = self.find_by_first_name(first_name)
        return child._parents[0] if child else None

    def find_monsters(self) -> List[Character]:
        return [c for c in self._allCharacters if c.isMonster]

    def find_family_by_character(self, first_name: str) -> List[Character]:
        person = self.find_by_first_name(first_name)
        if not person:
            return []
        family = set(person._parents) | set(person._children) | set(person._siblings)
        return list(family)

    def find_family_by_last_name(self, last_name: Optional[str]) -> List[Character]:
        family = [c for c in self._allCharacters if c.lastName == last_name]
        if last_name is None:
            family_without_monsters = [c for c in family if not c.isMonster]
            return family_without_monsters
        return family
