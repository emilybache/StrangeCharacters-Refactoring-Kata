namespace Characters;

public class CharacterFinder
{
    private readonly List<Character> _allCharacters;

    public CharacterFinder(List<Character> allCharacters)
    {
        _allCharacters = allCharacters;
    }

    public Character? FindByFirstName(string name)
    {
        
        var found = _allCharacters.FindAll(c => c.FirstName == name);
        if (found.Count > 0)
        {
            var character = found[0];
            return character;
        }
        else
        {
            return null;
        }
    }
    
    public Character? FindParent(string firstName)
    {
        var child = FindByFirstName(firstName);
        if (child == null)
        {
            return null;
        }
        var parent = child?.parents.First();
        return parent;
    }

    public List<Character> FindMonsters()
    {
        var monsters = _allCharacters.FindAll(c => c.IsMonster);
        return monsters;
    }
    
    public List<Character> FindFamilyByCharacter(string firstName)
    {
        var person = FindByFirstName(firstName);
        if (person == null)
        {
            return new List<Character>();
        }
        var family = new HashSet<Character>();
        family.UnionWith(person.parents);
        family.UnionWith(person.children);
        family.UnionWith(person.siblings);
        
        return family.ToList();
    }
    
    public List<Character> FindFamilyByLastName(string? lastName)
    {
        var family = _allCharacters.FindAll(c => c.LastName == lastName);

        if (lastName == null)
        {
            var familyWithoutMonsters = family.FindAll(c => !c.IsMonster);
            return familyWithoutMonsters.ToList();
        }

        return family;
    }
    
}