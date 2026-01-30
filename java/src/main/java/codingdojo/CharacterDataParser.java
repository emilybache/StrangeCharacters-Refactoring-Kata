package codingdojo;

import com.fasterxml.jackson.core.type.TypeReference;
import com.fasterxml.jackson.databind.ObjectMapper;

import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.regex.Pattern;

public class CharacterDataParser {
    private static List<Character> allCharacters = new ArrayList();
    private static CharacterFinder characterFinder;

    public static void probably_InitializeFromFile_AndStuff(String filename) throws IOException {
        if (filename == null) {
            filename = "strange_characters.json";
        }
        ClassLoader classloader = Thread.currentThread().getContextClassLoader();
        InputStream inputStream = classloader.getResourceAsStream(filename);
        ObjectMapper mapper = new ObjectMapper();
        List<CharacterData> data = mapper.readValue(inputStream, new TypeReference<List<CharacterData>>() {});

        allCharacters = applesauce(data);
        characterFinder = new CharacterFinder(allCharacters);
    }

    private static List<Character> applesauce(List<CharacterData> data) {
        List<Character> result = new ArrayList<>();
        for (var characterData : data) {
            var character = new Character(characterData.FirstName, characterData.LastName, characterData.IsMonster);
            result.add(character);
        }

        for (var characterData : data) {

            // find nemesis
            if (characterData.Nemesis != null) {
                var nemesis = findCharacter(characterData.Nemesis, result);
                var character = findCharacter(characterData.FirstName, result);
                character.setNemesis(nemesis);
            }

            // add family
            if (characterData.Children != null) {
                var character = findCharacter(characterData.FirstName, result);
                for (var childName : characterData.Children) {
                    var child = findCharacter(childName, result);
                    if (child != null)
                        character.addChild(child);
                }
            }
        }
        return result;
    }

    private static Character findCharacter(String firstName, List<Character> characters) {
        return characters.stream().filter(c -> c.firstName.equals(firstName)).findFirst().orElseThrow();
    }

    public static Character evaluatePath(String path) {
        Character character = null;

        boolean hasFamilyName = false;
        String characterName = "";
        var familyName = "";
        var tempPathWithoutAttribute = new StringBuilder();
        String characterAttribute = "";
        var structureList = path.split("/");
        for (var i = structureList.length - 1; i >= 0; i--) {
            if (structureList[i].isEmpty())
                continue;
            var localName = "";
            var localNameWithoutAttribute = "";
            var familyLocalNameList = structureList[i].split(":");
            if (familyLocalNameList.length == 2) {
                if (!hasFamilyName) {
                    familyName = familyLocalNameList[0];
                    hasFamilyName = true;
                }

                familyName = familyLocalNameList[0];
                localName = familyLocalNameList[1];
            } else if (familyLocalNameList.length == 1) {
                localName = familyLocalNameList[0];
            }

            if (i == structureList.length - 1) {
                characterName = localName;
            }

            localNameWithoutAttribute = localName.replaceAll("\\{[^\\{]*?\\}", "");
            var pattern = Pattern.compile("(.*)\\{([^\\{]*)\\}");
            var matcher = pattern.matcher(localName);
            if (matcher.find() && matcher.groupCount() > 0) {
                characterAttribute = matcher.group(2);
                characterName = matcher.group(1);
            }

            tempPathWithoutAttribute.insert(0, "/" + localNameWithoutAttribute);
        }

        if (!hasFamilyName) {
            character = characterFinder.findByFirstName(characterName);
            if (characterAttribute != null && characterAttribute.equals("Nemesis")) {
                return character.getNemesis();
            }
            return character;
        }

        var filteredCharacters = characterFinder.findFamilyByLastName(familyName);
        if (!filteredCharacters.isEmpty()) {
            var names = Arrays.stream(tempPathWithoutAttribute.toString().split("/")).filter(n -> !n.isEmpty()).toList();
            if (names.size() == 2) {
                var firstName = names.get(1);
                character = filteredCharacters.stream().filter(c -> Objects.equals(c.firstName, firstName)).findFirst().orElse(null);
            }
            if (character != null && characterAttribute != null && characterAttribute.equals("Nemesis")) {
                return character.getNemesis();
            }
        }

        return character;
    }

}
