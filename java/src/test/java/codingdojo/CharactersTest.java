package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertIterableEquals;

class CharactersTest {

    @Test
    public void findCharacterByFirstName() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var character = finder.findByFirstName("Jim");
        assertEquals("Jim", character.firstName);
    }

    @Test
    public void FindElevenByLastName() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var characters = finder.findFamilyByLastName(null);
        assertIterableEquals(characters, List.of(new Character("Eleven")));
    }

    @Test
    public void FindParent() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var parent = finder.findParent("Nancy");
        assertEquals("Karen", parent.firstName);
    }

    @Test
    public void FindNoParent() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var parent = finder.findParent("George");
        assertEquals(null, parent);
    }

    @Test
    public void FindMonsters() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var monsters = finder.findMonsters();
        assertIterableEquals(List.of(
                new Character("Mindflayer"),
                new Character("Demagorgon"),
                new Character("Demadog")
        ), monsters);
    }

    @Test
    public void FindFamily() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var family = finder.findFamilyByCharacter("Jim");
        assertIterableEquals(List.of(
                new Character("Eleven")
        ), family);
    }

    @Test
    public void FindFamilyByLastName() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var family = finder.findFamilyByLastName("Wheeler");
        assertIterableEquals(List.of(
                new Character("Mike", "Wheeler"),
                new Character("Nancy", "Wheeler"),
                new Character("Karen", "Wheeler")
        ), family);
    }

    @Test
    public void FindNothingByName() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var character = finder.findByFirstName("George");
        assertEquals(null, character);
    }

    @Test
    public void FindNoFamily() {
        var finder = new CharacterFinder(CharacterFactory.allTestData());
        var characters = finder.findFamilyByCharacter("George");
        assertEquals(characters.size(), 0);
    }

    private static List<String> firstNames(List<Character> characters) {
        return characters.stream().map(f -> f.firstName).toList();
    }
}