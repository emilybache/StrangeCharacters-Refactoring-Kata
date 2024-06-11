/*
Main entry point for Characters program. Sample:

Using characters file: strange_characters.json
Please enter the character path: (type 'exit' to exit program)
Eleven
Character: Character(Eleven, , isMonster:False)
Please enter the character path: (type 'exit' to exit program)
Eleven{Nemesis}
Character: Character(Demagorgon, , isMonster:True)
Please enter the character path: (type 'exit' to exit program)
exit

 */
using Characters;

string? filename = null;
if (args.Length > 0)
{
    filename = args[0];
    Console.WriteLine("Using characters file: " + filename);
}
CharacterParser.InitializeFromFile(filename);

while (true)
{
    Console.WriteLine("Please enter the character path: (type 'exit' to exit program)");

    var path = Console.ReadLine();

    if (path == "exit")
    {
        break;
    }
    var character = CharacterParser.EvaluatePath(path);

    Console.WriteLine("Character: " + character);
   
}

