<?php

declare(strict_types=1);

use StrangeCharacters\CharacterDataParser;

require __DIR__ . '/vendor/autoload.php';

$filename = null;
if ($argc > 1) {
    $filename = $argv[1];
    echo "Using character file: $filename" . PHP_EOL;
}
CharacterDataParser::probably_InitializeFromFile_AndStuff($filename);

while (true) {
    echo "Please enter the path to evaluate: (type 'exit' to exit program)";

    $path = readline();

    if ("exit" ===$path) {
        break;
    }
    $character = CharacterDataParser::evaluatePath($path);

    echo "Character: $character";
}