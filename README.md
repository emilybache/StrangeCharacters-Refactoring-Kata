_Support this and all my katas via [Patreon](https://www.patreon.com/EmilyBache)_

Strange Characters Refactoring Kata
===================================

You can use this exercise starting point to practice refactoring. Kata Description: [Strange Characters Kata](https://www.sammancoaching.org/kata_descriptions/strange_characters.html). You could try practicing these refactorings:

* Convert a static class into a normal class
* Extract method where you have more than one return value
* Naming as a process

You can also use this code to learn about designing tests that make assertions on complex objects and data structures.

There is a video explaining one way to use this exercise [Trustworthy Code with Naming as a Process](https://youtu.be/PPQHJpWG4GA). If you like this kata, you may be interested in [my books](https://leanpub.com/u/emilybache) too.

Sample Program Output
---------------------
This is an example run of the program:

    Using character file: strange_characters.json
    Please enter the path to evaluate: (type 'exit' to exit program)
    /Byers/Will
    Character: Character(Will, Byers, isMonster:False)
    Please enter the path to evaluate: (type 'exit' to exit program)
    /Byers/Will{Nemesis}
    Character: Character(Mindflayer, , isMonster:True)
    Please enter the path to evaluate: (type 'exit' to exit program)
    exit

New requirement
---------------
You have been asked to modify the program to also support a query like this:

    /FamilyName/FirstName{Sibling}

So for example you'd like to be able to do this:

    Please enter the path to evaluate: (type 'exit' to exit program)
    /Byers/Will{Sibling}
    Character: Character(Will, Byers, isMonster:False)

This output is wrong - it should instead return the Character Jonathan Byers. Refactor the code as you need so you can add this feature cleanly.
