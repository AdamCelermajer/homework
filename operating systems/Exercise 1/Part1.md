PGN File Splitter Bash Script
========================================

Overview
--------

In this project, you will create a Bash script named `pgn_split.sh` that processes chess games recorded in Portable Game Notation (PGN) format. The script will split multiple chess games contained in a single PGN file into separate files within a specified destination directory.

Objectives
----------

* Validate the presence of required command-line arguments.
* Verify the existence of the source PGN file.
* Ensure the destination directory exists or create it if necessary.
* Split multiple chess games from the source PGN file into individual files.
* Use functions to manage file operations effectively.

Understanding PGN
-----------------

Portable Game Notation (PGN) is a standard format for recording chess games as plain text, including both the moves and metadata about the game. Here's a brief look at what's inside a PGN file:

- **Metadata**: Information such as event name, site, date, players, and game result. Each metadata entry is enclosed in square brackets.
- **Moves**: The sequence of moves made in the game, written in algebraic chess notation.

Example of a PGN file snippet:

\[Event "57th Capablanca Mem"\] \[Site "Havana CUB"\] \[Date "2024.05.03"\] \[Round "1"\] \[White "Andersen, Mad"\] \[Black "Quesada Perez, Luis Ernesto"\] \[Result "0-1"\] ...
*   e4 e5 2. Nf3 Nc6 3. Bb5 Nf6 4. d3 Bc5 ...

Script Requirements
-------------------

### Command-Line Arguments

The script must accept exactly two arguments:
- **Source PGN file**: The path to the PGN file containing multiple chess games.
- **Destination directory**: The directory where split game files will be saved.

### Expected Outputs and Behavior

- **Argument Validation**: If the number of arguments is incorrect, print: `"Usage: $0 <source_pgn_file> <destination_directory>"` and exit with status 1.
- **File Existence Check**: If the source file does not exist, print: `"Error: File '$input_file' does not exist."` and exit with status 1.
- **Directory Creation**: If the destination directory does not exist, create it and print: `"Created directory '$dest_dir'."`

Example Files and Folders
-------------------------

For your reference and testing:
- **`pgns/`**: This folder contains example PGN files with multiple games.
- **`splited_pgn/`**: This folder is the intended destination for the individual game files created by your script. You will find examples of split files here to understand the expected output format.

#### Usage

```bash
(base) itay@itayPC:~/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1$ ./split_pgn.sh
Usage: ./split_pgn.sh <source_pgn_file> <destination_directory>`
```
#### Incorrect Usage
```bash
(base) itay@itayPC:~/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1$ ./split_pgn.sh /home/itay/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1/pgns/capmemel24.pgn
Usage: ./split_pgn.sh <source_pgn_file> <destination_directory>
```

#### Correct Usage (Directory already exists)
```bash
(base) itay@itayPC:~/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1$ ./split_pgn.sh /home/itay/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1/pgns/capmemel24.pgn splited_pgn
Saved game to splited_pgn/capmemel24_1.pgn
Saved game to splited_pgn/capmemel24_2.pgn
Saved game to splited_pgn/capmemel24_3.pgn
Saved game to splited_pgn/capmemel24_4.pgn
Saved game to splited_pgn/capmemel24_5.pgn
Saved game to splited_pgn/capmemel24_6.pgn
Saved game to splited_pgn/capmemel24_7.pgn
Saved game to splited_pgn/capmemel24_8.pgn
Saved game to splited_pgn/capmemel24_9.pgn
All games have been split and saved to 'splited_pgn'.
```

#### Correct Usage (Creating Directory)
```bash
(base) itay@itayPC:~/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1$ ./split_pgn.sh /home/itay/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1/pgns/capmemel24.pgn splitedddddddd_pgn
Created directory 'splitedddddddd_pgn'.
Saved game to splitedddddddd_pgn/capmemel24_1.pgn
Saved game to splitedddddddd_pgn/capmemel24_2.pgn
Saved game to splitedddddddd_pgn/capmemel24_3.pgn
Saved game to splitedddddddd_pgn/capmemel24_4.pgn
Saved game to splitedddddddd_pgn/capmemel24_5.pgn
Saved game to splitedddddddd_pgn/capmemel24_6.pgn
Saved game to splitedddddddd_pgn/capmemel24_7.pgn
Saved game to splitedddddddd_pgn/capmemel24_8.pgn
Saved game to splitedddddddd_pgn/capmemel24_9.pgn
All games have been split and saved to 'splitedddddddd_pgn'.
```

#### Error Handling
```bash
(base) itay@itayPC:~/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1$ ./split_pgn.sh /home/itay/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1/pgns/capmemel24 splited_pgn
Error: File '/home/itay/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1/pgns/capmemel24' does not exist.
```


