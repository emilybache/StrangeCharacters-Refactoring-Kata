package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertIterableEquals;

class CharactersTest {
    public Collection<Character> allTestData() {
        var joyce = new Character("Joyce", "Byers");
        var jim = new Character("Jim", "Hopper");
        var mike = new Character("Mike", "Wheeler");
        var eleven = new Character("Eleven");
        var dustin = new Character("Dustin", "Henderson");
        var lucas = new Character("Lucas", "Sinclair");
        var nancy = new Character("Nancy", "Wheeler");
        var jonathan = new Character("Jonathan", "Byers");
        var will = new Character("Will", "Byers");
        var karen = new Character("Karen", "Wheeler");
        var steve = new Character("Steve", "Harrington");
        var mindflayer = new Character("Mindflayer", true);
        var demagorgon = new Character("Demagorgon", true);
        var demadog = new Character("Demadog", true);

        joyce.addChild(jonathan);
        joyce.addChild(will);
        jim.addChild(eleven);
        karen.addChild(nancy);
        karen.addChild(mike);

        eleven.setNemesis(demagorgon);
        will.setNemesis(mindflayer);
        dustin.setNemesis(demadog);

        return Arrays.asList(
                joyce,
                jim,
                mike,
                will,
                eleven,
                dustin,
                lucas,
                nancy,
                jonathan,
                mindflayer,
                demagorgon,
                demadog,
                karen,
                steve);
    }

    @Test
    public void findCharacterByFirstName() {
        var finder = new CharacterFinder(allTestData());
        var character = finder.findByFirstName("Jim");
        assertEquals("Jim", character.firstName);
    }

    @Test
    public void FindElevenByLastName() {
        var finder = new CharacterFinder(allTestData());
        var characters = finder.findFamilyByLastName(null);
        assertIterableEquals(characters, List.of(new Character("Eleven")));
    }

    @Test
    public void FindParent() {
        var finder = new CharacterFinder(allTestData());
        var parent = finder.findParent("Nancy");
        assertEquals("Karen", parent.firstName);
    }

    @Test
    public void FindNoParent() {
        var finder = new CharacterFinder(allTestData());
        var parent = finder.findParent("George");
        assertEquals(null, parent);
    }

    @Test
    public void FindMonsters() {
        var finder = new CharacterFinder(allTestData());
        var monsters = finder.findMonsters();
        assertIterableEquals(List.of(

                new Character("Mindflayer"),
                new Character("Demagorgon"),
                new Character("Demadog")
        ), monsters);
    }

    @Test
    public void FindFamily() {
        var finder = new CharacterFinder(allTestData());
        var family = finder.findFamilyByCharacter("Jim");
        assertIterableEquals(List.of(
                new Character("Eleven")
        ), family);
    }

    @Test
    public void FindFamilyByLastName() {
        var finder = new CharacterFinder(allTestData());
        var family = finder.findFamilyByLastName("Wheeler");
        assertIterableEquals(List.of(
                new Character("Mike", "Wheeler"),
                new Character("Nancy", "Wheeler"),
                new Character("Karen", "Wheeler")
        ), family);
    }

    @Test
    public void FindNothingByName() {
        var finder = new CharacterFinder(allTestData());
        var character = finder.findByFirstName("George");
        assertEquals(null, character);
    }

    @Test
    public void FindNoFamily() {
        var finder = new CharacterFinder(allTestData());
        var characters = finder.findFamilyByCharacter("George");
        assertEquals(characters.size(), 0);
    }
}