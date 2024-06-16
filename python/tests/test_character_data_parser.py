import pytest

from character_data_parser import probably_initialize_from_file_and_stuff, evaluate_path


@pytest.mark.parametrize("path, expected_first_name", [
    ("/Jim/Eleven", "Eleven"),
    ("", None),
    ("/Wheeler:Karen/Wheeler:Nancy", "Nancy"),
    ("/Joyce/Will{Nemesis}", "Mindflayer"),
    ("/Wheeler:Karen/Wheeler:Nancy{Nemesis}", None),
    ("/Wheeler:Karen/Wheeler:George", None)
])
def test_find_character_by_path(path, expected_first_name, strange_characters_filename):
    probably_initialize_from_file_and_stuff(strange_characters_filename)
    character = evaluate_path(path)
    if expected_first_name is None:
        assert character is None
    else:
        assert character.firstName == expected_first_name
