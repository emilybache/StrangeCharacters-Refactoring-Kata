package codingdojo;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws Exception {
        String filename = null;
        if (args.length > 0) {
            filename = args[0];
            System.out.println("Using character file: " + filename);
        }
        CharacterDataParser.probably_InitializeFromFile_AndStuff(filename);

        while (true) {
            System.out.println("Please enter the path to evaluate: (type 'exit' to exit program)");

            String path = System.console().readLine();

            if ("exit".equals(path)) {
                break;
            }
            var character = CharacterDataParser.evaluatePath(path);

            System.out.println("Character: " + character);
        }
    }
}
