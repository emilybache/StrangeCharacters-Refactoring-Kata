using Characters;
using NUnit.Framework;

namespace TestCharacters;

/*
 * This test case shows what's possible with collection assertions
 */
public class ExampleCharacterTestCase
{
    [TestCase]
    public void OneCharacterTests()
    {
        // Arrange
        var nancy = new Character("Nancy", "Wheeler");
    
        // No Act step - we will just illustrate some assertions you can do on a Character
        
        // Assert
        Assert.AreEqual("Nancy", nancy.FirstName);
        Assert.AreEqual(nancy, nancy);
        // This assertion works because Character implements "Equals"
        Assert.AreEqual(new Character("Nancy", "Wheeler"), nancy);
    }
    
    [TestCase]
    public void CharacterListTests()
    {
        // Arrange
        var charactersList = CharacterFactory.WheelerFamily();
        
        // No Act step - we will just illustrate some assertions you can do on a List of Characters

        // Assert
        Assert.NotNull(charactersList);
        Assert.AreEqual(3, charactersList.Count);
        CollectionAssert.Contains(charactersList, new Character("Nancy", "Wheeler"));
        CollectionAssert.AreEquivalent(new List<Character>()
        {
            new Character("Nancy", "Wheeler"),
            new Character("Mike", "Wheeler"),
            new Character("Karen", "Wheeler"),
        }, charactersList);
        Assert.AreEqual(new List<Character>()
        {
            new Character("Karen", "Wheeler"),
            new Character("Mike", "Wheeler"),
            new Character("Nancy", "Wheeler"),
        }, charactersList);
    }
}