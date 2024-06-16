import json
from character import Character, CharacterFinder
import re

character_finder = None


def probably_initialize_from_file_and_stuff(file_name=None):
    file_name = file_name or "strange_characters.json"
    with open(file_name, "r", encoding="utf-8") as file:
        data = json.load(file)

    all_characters = applesauce(data)
    global character_finder
    character_finder = CharacterFinder(all_characters)


def applesauce(data):
    result = []
    for character_data in data:
        character = Character(character_data["FirstName"], character_data["LastName"], character_data["IsMonster"])
        result.append(character)

    for character_data in data:
        # find nemesis
        if character_data["Nemesis"]:
            nemesis = find_character(result, character_data["Nemesis"])
            character = find_character(result, character_data["FirstName"])
            if character:
                character._nemesis = nemesis

        # add family
        if character_data.get("Children"):
            character = find_character(result, character_data["FirstName"])
            for child_name in character_data["Children"]:
                child = find_character(result, child_name)
                if child:
                    character._add_child(child)

    return result


def find_character(characters, first_name):
    found = [c for c in characters if c.firstName == first_name]
    if found:
        return found[0]
    return None


def evaluate_path(path):
    character = None
    has_family_name = False
    character_name = ""
    family_name = ""
    temp_path_without_curly_braces = ""
    curly_braces = ""
    structure_list = path.split("/")

    for i in range(len(structure_list) - 1, -1, -1):
        local_name = ""
        local_name_without_curly_braces = ""
        family_local_name_list = structure_list[i].split(":")

        if len(family_local_name_list) == 2:
            if not has_family_name:
                family_name = family_local_name_list[0]
                has_family_name = True
            family_name = family_local_name_list[0]
            local_name = family_local_name_list[1]
        elif len(family_local_name_list) == 1:
            local_name = family_local_name_list[0]

        if i == len(structure_list) - 1:
            character_name = local_name

        local_name_without_curly_braces = re.sub(r'{[^{]*?}', '', local_name)
        matches = re.findall(r'(.*){([^}]*)}', local_name)

        for match in matches:
            groups = match
            curly_braces = groups[1]
            character_name = groups[0]

        temp_path_without_curly_braces = f"/{local_name_without_curly_braces}" + temp_path_without_curly_braces

    if not has_family_name:
        character = character_finder.find_by_first_name(character_name)
        if character and curly_braces and curly_braces == "Nemesis":
            character = character_finder.find_by_first_name(character_name)
            if character and curly_braces and curly_braces == "Nemesis":
                return character._nemesis
            return character

    filtered_characters = character_finder.find_family_by_last_name(family_name)
    if filtered_characters:
        names = temp_path_without_curly_braces.split("/")
        first_name = names[-1]
        found = [c for c in filtered_characters if c.firstName == first_name]
        if found:
            character = found[0]
        else:
            character = None

        if character and curly_braces and curly_braces == "Nemesis":
            return character._nemesis

    return character

