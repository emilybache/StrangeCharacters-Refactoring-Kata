package codingdojo;

import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class CharacterParserTest
{
    @Test
    public void findCharacterByPath() throws IOException {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.evaluatePath("/Jim/Eleven");
        assertEquals("Eleven", character.firstName);
    }
    
    @Test
    public void findCharacterByEmptyPath() throws IOException {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.evaluatePath("");
        assertNull(character);
    }

    @Test
    public void FindCharacterByPathWithFamilyName() throws IOException {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.evaluatePath("/Wheeler:Karen/Wheeler:Nancy");
        assertEquals("Nancy", character.firstName);
    }
    
    @Test
    public void FindNemesisByPath() throws IOException {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.evaluatePath("/Joyce/Will{Nemesis}");
        assertEquals("Mindflayer", character.firstName);
    }
    
    @Test
    public void FindNemesisByPathAndFamilyName() throws IOException {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.evaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
        assertEquals(null, character);
    }
    
    @Test
    public void FindNothingByPathAndFamilyName() throws IOException {
        CharacterParser.InitializeFromFile(null);
        var character = CharacterParser.evaluatePath("/Wheeler:Karen/Wheeler:George");
        assertEquals(null, character);
    }
}
