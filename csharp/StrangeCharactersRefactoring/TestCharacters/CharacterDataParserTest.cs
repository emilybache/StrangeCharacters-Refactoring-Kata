using Characters;
using NUnit.Framework;

namespace TestCharacters;

public class CharacterDataParserTest
{
    [TestCase]
    public void FindCharacterByPath()
    {
        CharacterDataParser.Probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.EvaluatePath("/Jim/Eleven");
        Assert.AreEqual("Eleven", character?.FirstName);
    }
    
    [TestCase]
    public void FindCharacterByEmptyPath()
    {
        CharacterDataParser.Probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.EvaluatePath("");
        Assert.Null(character);
    }

    [TestCase]
    public void FindCharacterByPathWithFamilyName()
    {
        CharacterDataParser.Probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.EvaluatePath("/Wheeler:Karen/Wheeler:Nancy");
        Assert.AreEqual("Nancy", character?.FirstName);
    }
    
    [TestCase]
    public void FindNemesisByPath()
    {
        CharacterDataParser.Probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.EvaluatePath("/Joyce/Will{Nemesis}");
        Assert.AreEqual("Mindflayer", character?.FirstName);
    }
    
    [TestCase]
    public void FindNemesisByPathAndFamilyName()
    {
        CharacterDataParser.Probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.EvaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
        Assert.AreEqual(null, character);
    }
    
    [TestCase]
    public void FindNothingByPathAndFamilyName()
    {
        CharacterDataParser.Probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.EvaluatePath("/Wheeler:Karen/Wheeler:George");
        Assert.AreEqual(null, character);
    }
}