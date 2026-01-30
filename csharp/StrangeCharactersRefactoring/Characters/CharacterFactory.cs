namespace Characters;

/**
 * Factory for commonly used lists of Characters
 */
public class CharacterFactory
{
    public static List<Character> StrangeCharacters()
    {
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
        var holly = new Character("Holly", "Wheeler");
        var steve = new Character("Steve", "Harrington");
        var mindflayer = new Character("Mindflayer", isMonster:true);
        var demagorgon = new Character("Demagorgon", isMonster:true);
        var demadog = new Character("Demadog", isMonster:true);
        var mrwhatsit = new Character("MrWhatsit", isMonster:true);
        
        joyce.AddChild(jonathan);
        joyce.AddChild(will);
        jim.AddChild(eleven);
        karen.AddChild(nancy);
        karen.AddChild(mike);
        karen.AddChild(holly);
        
        eleven.SetNemesis(demagorgon);
        will.SetNemesis(mindflayer);
        dustin.SetNemesis(demadog);
        holly.SetNemesis(mrwhatsit);

        return new List<Character>()
        {
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
            holly,
            steve,
            mrwhatsit
        };
    }

    public static List<Character> WheelerFamily()
    {
        var karen = new Character("Karen", "Wheeler");
        var mike = new Character("Mike", "Wheeler");
        var nancy = new Character("Nancy", "Wheeler");
        var holly = new Character("Holly", "Wheeler");

        karen.AddChild(nancy);
        karen.AddChild(mike);
        karen.AddChild(holly);

        return new List<Character>()
        {
            karen,
            mike,
            nancy,
        };
    }
}