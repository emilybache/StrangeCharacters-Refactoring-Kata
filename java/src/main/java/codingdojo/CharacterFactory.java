package codingdojo;

import java.util.Arrays;
import java.util.Collection;

public class CharacterFactory {
    public static Collection<Character> allTestData() {
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

    public static Collection<Character> wheelerFamily() {
        Character karen = new Character("Karen", "Wheeler");
        Character mike = new Character("Mike", "Wheeler");
        Character nancy = new Character("Nancy", "Wheeler");

        karen.addChild(nancy);
        karen.addChild(mike);

        return Arrays.asList(karen, mike, nancy);
    }
}
