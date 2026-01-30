import approvaltests
import pytest

from character import Character, CharacterFinder
from character_factory import CharacterFactory


def test_find_character_by_first_name():
    finder = CharacterFinder(CharacterFactory.strange_characters())
    character = finder.find_by_first_name("Jim")
    assert character is not None
    assert character.firstName == "Jim"


def test_find_eleven_by_last_name():
    finder = CharacterFinder(CharacterFactory.strange_characters())
    null_string = None
    characters = finder.find_family_by_last_name(null_string)
    assert any(c.firstName == "Eleven" for c in characters)


def test_find_parent():
    finder = CharacterFinder(CharacterFactory.strange_characters())
    parent = finder.find_parent("Nancy")
    assert parent is not None
    assert parent.firstName == "Karen"


def test_find_no_parent():
    finder = CharacterFinder(CharacterFactory.strange_characters())
    parent = finder.find_parent("George")
    assert parent is None


def test_find_monsters():
    finder = CharacterFinder(CharacterFactory.strange_characters())
    monsters = finder.find_monsters()
    approvaltests.verify_all("Monsters", monsters)


def test_find_family():
    finder = CharacterFinder(CharacterFactory.strange_characters())
    family = finder.find_family_by_character("Jim")
    expected_family = [Character("Eleven")]
    assert all(f in family for f in expected_family)
