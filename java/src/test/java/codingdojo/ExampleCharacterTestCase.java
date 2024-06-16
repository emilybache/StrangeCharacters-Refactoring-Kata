package codingdojo;

import org.junit.jupiter.api.Test;

import java.util.Arrays;
import java.util.Collection;
import java.util.stream.Collectors;

import static org.junit.jupiter.api.Assertions.*;

class ExampleCharacterTestCase {

    @Test
    void oneCharacterTests() {
        // Arrange
        Character nancy = new Character("Nancy", "Wheeler");

        // No Act step - we will just illustrate some assertions you can do on a Character

        // Assert
        assertEquals("Nancy", nancy.firstName);
        // This assertion works because Character implements "equals"
        assertEquals(new Character("Nancy", "Wheeler"), nancy);
    }

    @Test
    void characterListTests() {
        // Arrange
        Collection<Character> charactersList = CharacterFactory.wheelerFamily();

        // No Act step - we will just illustrate some assertions you can do on a List of Characters

        // Assert
        assertNotNull(charactersList);
        assertEquals(3, charactersList.size());
        assertTrue(charactersList.contains(new Character("Nancy", "Wheeler")));
        assertIterableEquals(Arrays.asList(
                new Character("Karen", "Wheeler"),
                new Character("Mike", "Wheeler"),
                new Character("Nancy", "Wheeler")
        ), charactersList.stream().sorted().toList());
        assertLinesMatch(Arrays.asList(
                "Karen Wheeler",
                "Mike Wheeler",
                "Nancy Wheeler"
        ), charactersList.stream()
                .map(c -> c.firstName + " " + c.lastName)
                .collect(Collectors.toList()));
    }
}

