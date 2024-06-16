from character import Character
from character_factory import CharacterFactory


def test_one_character():
    # Arrange
    nancy = Character("Nancy", "Wheeler")

    # No Act step - we will just illustrate some assertions you can do on a Character

    # Assert
    assert nancy.firstName == "Nancy"
    assert nancy == nancy
    # This assertion works because Character implements "__eq__"
    assert nancy == Character("Nancy", "Wheeler")


def test_character_list():
    # Arrange
    characters_list = CharacterFactory.wheeler_family()

    # No Act step - we will just illustrate some assertions you can do on a List of Characters

    # Assert
    assert characters_list is not None
    assert len(characters_list) == 3
    assert any(char.firstName == "Nancy" for char in characters_list)
    assert set(characters_list) == {
        Character("Nancy", "Wheeler"),
        Character("Mike", "Wheeler"),
        Character("Karen", "Wheeler"),
    }
    assert sorted(characters_list, key=lambda char: char.firstName) == [
        Character("Karen", "Wheeler"),
        Character("Mike", "Wheeler"),
        Character("Nancy", "Wheeler"),
    ]
