using Characters;
using NUnit.Framework;

namespace TestCharacters;

public class CharacterParserTest
{
    [TestCase]
    public void FindCharacterByPath()
    {
        CharacterParser.Certainly_InitializeFromFile_AndStuff(null);
        var character = CharacterParser.EvaluatePath("/Jim/Eleven");
        Assert.AreEqual("Eleven", character?.FirstName);
    }
    
    [TestCase]
    public void FindCharacterByEmptyPath()
    {
        CharacterParser.Certainly_InitializeFromFile_AndStuff(null);
        var character = CharacterParser.EvaluatePath("");
        Assert.Null(character);
    }

    [TestCase]
    public void FindCharacterByPathWithFamilyName()
    {
        CharacterParser.Certainly_InitializeFromFile_AndStuff(null);
        var character = CharacterParser.EvaluatePath("/Wheeler:Karen/Wheeler:Nancy");
        Assert.AreEqual("Nancy", character?.FirstName);
    }
    
    [TestCase]
    public void FindNemesisByPath()
    {
        CharacterParser.Certainly_InitializeFromFile_AndStuff(null);
        var character = CharacterParser.EvaluatePath("/Joyce/Will{Nemesis}");
        Assert.AreEqual("Mindflayer", character?.FirstName);
    }
    
    [TestCase]
    public void FindNemesisByPathAndFamilyName()
    {
        CharacterParser.Certainly_InitializeFromFile_AndStuff(null);
        var character = CharacterParser.EvaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
        Assert.AreEqual(null, character);
    }
    
    [TestCase]
    public void FindNothingByPathAndFamilyName()
    {
        CharacterParser.Certainly_InitializeFromFile_AndStuff(null);
        var character = CharacterParser.EvaluatePath("/Wheeler:Karen/Wheeler:George");
        Assert.AreEqual(null, character);
    }
}