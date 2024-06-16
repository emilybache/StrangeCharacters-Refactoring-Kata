# Main entry point for Strange Characters program.

from character_data_parser import probably_initialize_from_file_and_stuff, evaluate_path

filename = None
args = []  # Assuming args are provided elsewhere in your Python script

if args:
    filename = args[0]
    print(f"Using character file: {filename}")

probably_initialize_from_file_and_stuff(filename)

while True:
    print("Please enter the path to evaluate: (type 'exit' to exit program)")
    path = input()

    if path == "exit":
        break

    character = evaluate_path(path)
    print(f"Character: {character}")
