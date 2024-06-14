// Main entry point for Strange Characters program.

using Characters;

string? filename = null;
if (args.Length > 0)
{
    filename = args[0];
    Console.WriteLine("Using character file: " + filename);
}
CharacterDataParser.Probably_InitializeFromFile_AndStuff(filename);

while (true)
{
    Console.WriteLine("Please enter the path to evaluate: (type 'exit' to exit program)");

    var path = Console.ReadLine();

    if (path == "exit")
    {
        break;
    }
    var character = CharacterDataParser.EvaluatePath(path);

    Console.WriteLine("Character: " + character);
   
}

