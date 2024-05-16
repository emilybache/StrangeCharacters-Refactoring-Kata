package codingdojo;

import java.util.*;

import static java.util.stream.Collectors.toList;

public class CharacterFinder {
  private final Collection<Character> allCharacters;

  public CharacterFinder(Collection<Character> allCharacters) {
    this.allCharacters = allCharacters;
  }

  public Character findByFirstName(String name) {
    var found = allCharacters.stream().filter(c -> c.firstName.equals(name)).toList();
    if (!found.isEmpty()) {
        return found.getFirst();
    } else {
      return null;
    }
  }

  public Character findParent(String firstName) {
    var child = findByFirstName(firstName);
    if (child == null) {
      return null;
    }

      return child.parents.stream().findFirst().orElse(null);
  }

  public List<Character> findMonsters() {
      return allCharacters.stream().filter(c -> c.isMonster).collect(toList());
  }

  public List<Character> findFamilyByCharacter(String firstName) {
    var person = findByFirstName(firstName);
    if (person == null) {
      return new ArrayList<>();
    }
    var family = new HashSet<Character>();
    family.addAll(person.parents);
    family.addAll(person.children);
    family.addAll(person.siblings);

    return family.stream().toList();
  }

  public List<Character> findFamilyByLastName(String lastName) {
    var family = allCharacters.stream().filter(c -> (c.lastName != null &&
      c.lastName.equals(lastName) || (lastName == null && c.lastName == null))).collect(toList());

    if (lastName == null)
    {
        var familyWithoutMonsters = family.stream().filter(c -> !c.isMonster);
        return familyWithoutMonsters.toList();
    }

    return family;
  }
}
