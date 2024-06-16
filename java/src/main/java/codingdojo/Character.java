package codingdojo;

import java.util.HashSet;
import java.util.Objects;

public class Character implements Comparable<Character> {
  public final String firstName;
  public final String lastName;
  public final boolean isMonster;

  private Character nemesis;

  HashSet<Character> children = new HashSet<>();
  HashSet<Character> parents = new HashSet<>();
  HashSet<Character> siblings = new HashSet<>();

  public Character(String firstName, String lastName, boolean isMonster) {
    this.firstName = firstName;
    this.lastName = lastName;
    this.isMonster = isMonster;
  }

  public Character(String firstName) {
    this(firstName, null, false);
  }

  public Character(String firstName, boolean isMonster) {
    this(firstName, null, isMonster);
  }

  public Character(String firstName, String lastName) {
    this(firstName, lastName, false);
  }

  void addChild(Character child) {
    children.add(child);
    child.parents.add(this);
    for (Character character : children) {
      if (!child.firstName.equals(character.firstName)) {
        child.siblings.add(character);
        character.siblings.add(child);
      }
    }
  }

  public Character getNemesis() {
    return nemesis;
  }

  void setNemesis(Character monster) {
    this.nemesis = monster;
  }

  @Override
  public String toString() {
    return String.format("Character(%s, %s, %s)", firstName, lastName, isMonster ? "True" : "False");
  }

  @Override
  public boolean equals(Object o) {
    if (this == o) return true;
    if (!(o instanceof Character character)) return false;
      return isMonster == character.isMonster && Objects.equals(firstName, character.firstName) && Objects.equals(lastName, character.lastName);
  }

  @Override
  public int hashCode() {
    return Objects.hash(firstName, lastName, isMonster);
  }

  @Override
  public int compareTo(Character o) {
    return firstName.compareTo(o.firstName);
  }
}
