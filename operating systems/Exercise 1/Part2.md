
Chess Simulator Bash Script
======================================

Overview
--------

In this part, you will develop a Bash script `chess_sim.sh` that simulates a chess game using Portable Game Notation (PGN) files. The script will utilize `parse_moves.py`, a provided Python script, to convert PGN moves to Universal Chess Interface (UCI) format for easier manipulation.

Objectives
----------

*   Parse chess games from PGN files.
*   Display and manipulate chess games in the terminal using Bash.
*   Convert chess notation from PGN to UCI using Python.

What is PGN?
------------

[Portable Game Notation (PGN)](https://en.wikipedia.org/wiki/Portable_Game_Notation) is a standard format for recording chess games, which includes both the moves and metadata about the chess game. PGN files are used to review and replay games.

What is UCI?
------------

The [Universal Chess Interface (UCI)](https://en.wikipedia.org/wiki/Universal_Chess_Interface) is a standard protocol for chess engines to communicate with user interfaces. It simplifies chess engine commands and responses, which is beneficial for this project.

Understanding `parse_moves.py`
------------------------------

This Python script converts chess moves from the PGN format into UCI format. The script takes a single string of chess moves in PGN notation and returns a list of moves in UCI format:

*   **Input**: A string of chess moves in PGN format.
*   **Output**: A list of moves in UCI format.

**Example Usage**:
`python3 parse_moves.py "1. e4 e5 2. Nf3 Nc6"`

**Output**:
`["e2e4", "e7e5", "g1f3", "b8c6"]`

** Make sure you install pip install chess before hand ***

Repository Contents
-------------------

*   **chess\_games/**: Contains various `.pgn` files.
*   **parse\_moves.py**: Python script for converting notation.
*   **chess\_sim.sh**: Your Bash script to run the simulation.

### Required Strings

Ensure the following output strings are used exactly as they are crucial for the consistency of the script's output:

*   "Move $current\_move/${#moves\_history\[@\]}"
*   "Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit:"
*   "No more moves available."
*   "Exiting."
*   "Invalid key pressed: $key"

### Key Bindings and Their Effects

Your script will interactively display the chess board and wait for the user to control the game using key presses. Each key has a specific function:

*   **'d' (Next Move)**: Pressing 'd' will advance the game by making the next move from the moves list. If the game is at the initial position (before any moves are made), pressing 'd' will apply the first move from the PGN file. If all moves have been displayed, a message "No more moves available." will be shown.
    
*   **'a' (Previous Move)**: Pressing 'a' will undo the last move, reverting the board to the previous state. If no moves have been made yet (i.e., the board is in the initial state), pressing 'a' will have no effect, and no changes will occur on the board.
    
*   **'w' (Go to Start)**: Pressing 'w' will reset the board to its initial state, clearing all moves that have been made. This is useful for starting the game over from the beginning without needing to restart the script.
    
*   **'s' (Go to End)**: Pressing 's' will apply all moves in sequence until the end of the game is reached. This allows you to quickly navigate to the final position of the game as recorded in the PGN file.
    
*   **'q' (Quit)**: Pressing 'q' will exit the script and end the session. A closing message "Exiting." will be displayed for confirmation.
    

### Expected Behavior and Handling Edge Cases

It is essential that your script handles various scenarios and edge cases gracefully:

*   **At Game Start**: If 'd' is pressed before any move is made, the script should display the board after the first move is applied. If 'a' is pressed at the start, there should be no effect since there are no moves to undo.
    
*   **At Game End**: If 'd' is pressed and there are no more moves to display, the script should clearly notify the user that no more moves are available.
    
*   **During Gameplay**: The script should accurately display the board state for each move, including special chess moves such as castling, en passant, and pawn promotion. Undoing any move should revert to the exact previous state, including restoring any captured pieces.
    
### Restrictions

*   **No `awk` or external scripting**: Your solution should rely solely on Bash and the provided Python script.
*   **Exact match for strings and board layout**: The appearance and output of your script should strictly follow the specified formats.


### Examples

Examples 1:

```bash
(base) itay@itayPC:~/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1$ ./chess_sim.sh splited_pgn/capmemel24_1.pgn
Metadata from PGN file:
[Event "57th Capablanca Mem"]
[Site "Havana CUB"]
[Date "2024.05.03"]
[Round "1"]
[White "Andersen,Mad"]
[Black "Quesada Perez,Luis Ernesto"]
[Result "0-1"]
[WhiteElo "2598"]
[BlackElo "2567"]
[EventDate "2024.05.03"]
[ECO "C65"]

Move 0/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  p  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  .  .  .  .  5
4 .  .  .  .  .  .  .  .  4
3 .  .  .  .  .  .  .  .  3
2 P  P  P  P  P  P  P  P  2
1 R  N  B  Q  K  B  N  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: d
Move 1/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  p  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  .  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  .  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  B  N  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: d
Move 2/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  .  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  p  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  .  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  B  N  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: d
Move 3/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  .  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  p  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  N  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  B  .  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: a
Move 2/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  .  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  p  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  .  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  B  N  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: a
Move 1/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  p  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  .  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  .  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  B  N  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: d
Move 2/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  .  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  p  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  .  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  B  N  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: d
Move 3/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  .  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  p  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  N  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  B  .  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: d
Move 4/114
  a b c d e f g h
8 r  .  b  q  k  b  n  r  8
7 p  p  p  p  .  p  p  p  7
6 .  .  n  .  .  .  .  .  6
5 .  .  .  .  p  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  N  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  B  .  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: d
Move 5/114
  a b c d e f g h
8 r  .  b  q  k  b  n  r  8
7 p  p  p  p  .  p  p  p  7
6 .  .  n  .  .  .  .  .  6
5 .  B  .  .  p  .  .  .  5
4 .  .  .  .  P  .  .  .  4
3 .  .  .  .  .  N  .  .  3
2 P  P  P  P  .  P  P  P  2
1 R  N  B  Q  K  .  .  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: s
Move 114/114
  a b c d e f g h
8 .  .  .  .  .  .  .  r  8
7 .  .  .  .  .  .  R  .  7
6 .  .  p  .  .  .  .  .  6
5 p  .  .  .  .  .  p  p  5
4 r  .  .  .  .  .  .  k  4
3 .  .  P  .  .  .  .  P  3
2 .  .  .  .  .  .  .  .  2
1 .  .  .  .  .  .  K  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: w
Move 0/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  p  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  .  .  .  .  5
4 .  .  .  .  .  .  .  .  4
3 .  .  .  .  .  .  .  .  3
2 P  P  P  P  P  P  P  P  2
1 R  N  B  Q  K  B  N  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: q
Exiting.
End of game.
```


Example 2:
```bash
(base) itay@itayPC:~/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1$ ./chess_sim.sh splited_pgn/capmemel24_1.pg
File does not exist: splited_pgn/capmemel24_1.pg
```

Example 3:
```bash
(base) itay@itayPC:~/Documents/Repos/Operation-Systems-Solutions/Operation-System-Solutions/Exercise1$ ./chess_sim.sh splited_pgn/capmemel24_1.pgn
Metadata from PGN file:
[Event "57th Capablanca Mem"]
[Site "Havana CUB"]
[Date "2024.05.03"]
[Round "1"]
[White "Andersen,Mad"]
[Black "Quesada Perez,Luis Ernesto"]
[Result "0-1"]
[WhiteElo "2598"]
[BlackElo "2567"]
[EventDate "2024.05.03"]
[ECO "C65"]

Move 0/114
  a b c d e f g h
8 r  n  b  q  k  b  n  r  8
7 p  p  p  p  p  p  p  p  7
6 .  .  .  .  .  .  .  .  6
5 .  .  .  .  .  .  .  .  5
4 .  .  .  .  .  .  .  .  4
3 .  .  .  .  .  .  .  .  3
2 P  P  P  P  P  P  P  P  2
1 R  N  B  Q  K  B  N  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: s
Move 114/114
  a b c d e f g h
8 .  .  .  .  .  .  .  r  8
7 .  .  .  .  .  .  R  .  7
6 .  .  p  .  .  .  .  .  6
5 p  .  .  .  .  .  p  p  5
4 r  .  .  .  .  .  .  k  4
3 .  .  P  .  .  .  .  P  3
2 .  .  .  .  .  .  .  .  2
1 .  .  .  .  .  .  K  R  1
  a b c d e f g h
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit: d
No more moves available.
Press 'd' to move forward, 'a' to move back, 'w' to go to the start, 's' to go to the end, 'q' to quit:
```
