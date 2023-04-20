using Characters;
using NUnit.Framework;

namespace TestCharacters;

public class CharacterParserTest
{
    [TestCase]
    public void FindCharacterByPath()
    {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.EvaluatePath("/Jim/Eleven");
        Assert.AreEqual("Eleven", character?.FirstName);
    }
    
    [TestCase]
    public void FindCharacterByEmptyPath()
    {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.EvaluatePath("");
        Assert.Null(character);
    }

    [TestCase]
    public void FindCharacterByPathWithFamilyName()
    {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.EvaluatePath("/Wheeler:Karen/Wheeler:Nancy");
        Assert.AreEqual("Nancy", character?.FirstName);
    }
    
    [TestCase]
    public void FindNemesisByPath()
    {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.EvaluatePath("/Joyce/Will{Nemesis}");
        Assert.AreEqual("Mindflayer", character?.FirstName);
    }
    
    [TestCase]
    public void FindNemesisByPathAndFamilyName()
    {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.EvaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
        Assert.AreEqual(null, character);
    }
    
    [TestCase]
    public void FindNothingByPathAndFamilyName()
    {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.EvaluatePath("/Wheeler:Karen/Wheeler:George");
        Assert.AreEqual(null, character);
    }
}