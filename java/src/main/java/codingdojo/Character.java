package codingdojo;

import java.util.HashSet;

public class Character {
  public final String firstName;
  public final String lastName;
  public final boolean isMonster;

  private Character nemesis;

  public HashSet<Character> children = new HashSet<>();
  public HashSet<Character> parents = new HashSet<>();
  public HashSet<Character> siblings = new HashSet<>();

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

  public void addChild(Character child) {
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

}
