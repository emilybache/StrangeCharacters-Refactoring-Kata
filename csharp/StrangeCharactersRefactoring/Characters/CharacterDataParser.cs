using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Text.RegularExpressions;

namespace Characters;

public class CharacterDataParser
{
    private static List<Character> allCharacters = new();
    
    public static void Probably_InitializeFromFile_AndStuff(string? fileName)
    {
        fileName ??= "strange_characters.json";
        string jsonString = File.ReadAllText(fileName, Encoding.UTF8);
        var data = JsonSerializer.Deserialize<List<CharacterData>>(jsonString)!;

        allCharacters = Applesauce(data);
    }

    private static List<Character> Applesauce(List<CharacterData> data)
    {
        List<Character> result = new();
        foreach (var characterData in data)
        {
            var character = new Character(characterData.FirstName, characterData.LastName, characterData.IsMonster);
            result.Add(character);
        }

        foreach (var characterData in data)
        {
            // find nemesis
            if (characterData.Nemesis != null)
            {
                var nemesis = FindCharacter(result, characterData.Nemesis);
                var character = FindCharacter(result, characterData.FirstName);
                character?.SetNemesis(nemesis);
            }

            // add family
            if (characterData.Children != null)
            {
                var character = FindCharacter(result, characterData.FirstName);
                foreach (var childName in characterData.Children)
                {
                    var child = FindCharacter(result, childName);
                    if (child != null)
                        character?.AddChild(child);
                }
            }
        }

        return result;
    }

    public static Character EvaluatePath(string path)
    {
        Character character = null;

        bool hasFamilyName = false;
        string characterName = String.Empty;
        var familyName = String.Empty;
        string tempPathWithoutCurlyBraces = String.Empty;
        string curlyBraces = String.Empty;
        var structureList = path?.Split(new string[] { "/" }, StringSplitOptions.RemoveEmptyEntries);
        for (var i = structureList.Length - 1; i >= 0; i--)
        {
            var localName = String.Empty;
            var localNameWithoutCurlyBraces = String.Empty;
            var familyLocalNameList = structureList[i].Split(":");
            if (familyLocalNameList.Length == 2)
            {
                if (!hasFamilyName)
                {
                    familyName = familyLocalNameList[0];
                    hasFamilyName = true;
                }

                familyName = familyLocalNameList[0];
                localName = familyLocalNameList[1];
            }
            else if (familyLocalNameList.Length == 1)
            {
                localName = familyLocalNameList[0];
            }

            if (i == structureList.Length - 1)
            {
                characterName = localName;
            }

            localNameWithoutCurlyBraces = Regex.Replace(localName, "{[^{]*?}", String.Empty);
            var matches = Regex.Matches(localName, "(.*){([^{]*)}");
            foreach (Match match in matches)
            {
                var groups = match.Groups;
                curlyBraces = groups[2].Value;
                characterName = groups[1].Value;
            }

            tempPathWithoutCurlyBraces = tempPathWithoutCurlyBraces.Insert(0, "/" + localNameWithoutCurlyBraces);
        }

        if (!hasFamilyName)
        {
            character = FindCharacter(allCharacters, characterName);
            if (curlyBraces != null && curlyBraces == "Nemesis")
            {
                return character.Nemesis;
            }
            return character;
        }

        var filteredCharacters = FilterCharactersByFamilyName(familyName, characterName);
        if (filteredCharacters.Any())
        {
            character = FindCharacterWithFamily(filteredCharacters, tempPathWithoutCurlyBraces);
            if (curlyBraces != null && curlyBraces == "Nemesis")
            {
                return character.Nemesis;
            }
        }
        
        return character;
    }

    private static Character? FindCharacterWithFamily(List<Character> filteredCharacters, string tempPathWithoutCurlyBraces)
    {
        var firstName = tempPathWithoutCurlyBraces.Split("/", StringSplitOptions.RemoveEmptyEntries).Last();
        var found = filteredCharacters.FindAll(c => c.FirstName == firstName);
        if (found.Count > 0)
        {
            return found.First();
        }

        return null;
    }

    private static List<Character> FilterCharactersByFamilyName(string familyName, string characterName)
    {
        var found = allCharacters.FindAll(c => c.LastName == familyName);
        if (allCharacters.Exists(c => c.FirstName == characterName))
        {
            return found;
        }

        return new List<Character>();
    }
    

    private static Character? FindCharacter(List<Character> characters, string firstName)
    {
        var found = characters.FindAll(c => c.FirstName == firstName);
        if (found.Count > 0)
        {
            return found.First();
        }
        return null;
    }
    
}

public class CharacterData
{
    [JsonPropertyName("FirstName")] public string FirstName { get; set; }

    [JsonPropertyName("LastName")] public string LastName { get; set; }
    [JsonPropertyName("IsMonster")] public bool IsMonster { get; set; }
    [JsonPropertyName("Nemesis")] public string? Nemesis { get; set; }
    [JsonPropertyName("Children")] public List<string>? Children { get; set; }
}

