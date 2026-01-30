using Characters;
using NUnit;
using NUnit.Framework;

namespace TestCharacters;

public class CharactersTest
{
    [TestCase]
    public void FindCharacterByFirstName()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        var character = finder.FindByFirstName("Jim");
        Assert.AreEqual("Jim", character?.FirstName);
    }

    [TestCase]
    public void FindElevenByLastName()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        string? nullString = null;
        var characters = finder.FindFamilyByLastName(nullString);
        CollectionAssert.Contains(characters, new Character("Eleven"));
    }

    [TestCase]
    public void FindParent()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        var parent = finder.FindParent("Nancy");
        Assert.AreEqual("Karen", parent?.FirstName);
    }
    
    [TestCase]
    public void FindNoParent()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        var parent = finder.FindParent("George");
        Assert.AreEqual(null, parent);
    }
    
    [TestCase]
    public void FindMonsters()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        var monsters = finder.FindMonsters();
        CollectionAssert.AreEquivalent(new List<Character>()
        {
            new Character("Mindflayer"),
            new Character("Demagorgon"),
            new Character("Demadog"),
            new Character("MrWhatsit"),
        }, monsters);
    }

    [TestCase]
    public void FindFamily()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        var family = finder.FindFamilyByCharacter("Jim");
        CollectionAssert.AreEquivalent(new List<Character>()
        {
            new Character("Eleven"),
        }, family);
    }
    [TestCase]
    public void FindFamilyByLastName()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        var family = finder.FindFamilyByLastName("Wheeler");
        CollectionAssert.AreEquivalent(new List<Character>()
        {
            new Character("Nancy", "Wheeler"),
            new Character("Mike", "Wheeler"),
            new Character("Karen", "Wheeler"),
            new Character("Holly", "Wheeler"),
        }, family);
    }
    
    [TestCase]
    public void FindNothingByName()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        var character = finder.FindByFirstName("George");
        Assert.AreEqual(null, character);
    }
    
    [TestCase]
    public void FindNoFamily()
    {
        var finder = new CharacterFinder(CharacterFactory.StrangeCharacters());
        var characters = finder.FindFamilyByCharacter("George");
        Assert.AreEqual(characters.Count, 0);
    }
}