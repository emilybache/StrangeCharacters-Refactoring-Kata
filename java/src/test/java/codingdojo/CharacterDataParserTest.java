package codingdojo;

import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNull;

public class CharacterDataParserTest
{
    @Test
    public void findCharacterByPath() throws IOException {
        CharacterDataParser.probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.evaluatePath("/Jim/Eleven");
        assertEquals("Eleven", character.firstName);
    }
    
    @Test
    public void findCharacterByEmptyPath() throws IOException {
        CharacterDataParser.probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.evaluatePath("");
        assertNull(character);
    }

    @Test
    public void FindCharacterByPathWithFamilyName() throws IOException {
        CharacterDataParser.probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.evaluatePath("/Wheeler:Karen/Wheeler:Nancy");
        assertEquals("Nancy", character.firstName);
    }
    
    @Test
    public void FindNemesisByPath() throws IOException {
        CharacterDataParser.probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.evaluatePath("/Joyce/Will{Nemesis}");
        assertEquals("Mindflayer", character.firstName);
    }
    
    @Test
    public void FindNemesisByPathAndFamilyName() throws IOException {
        CharacterDataParser.probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.evaluatePath("/Wheeler:Karen/Wheeler:Nancy{Nemesis}");
        assertEquals(null, character);
    }
    
    @Test
    public void FindNothingByPathAndFamilyName() throws IOException {
        CharacterDataParser.probably_InitializeFromFile_AndStuff(null);
        var character = CharacterDataParser.evaluatePath("/Wheeler:Karen/Wheeler:George");
        assertEquals(null, character);
    }
}
