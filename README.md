# 2048 Game in C

A console-based implementation of the classic 2048 puzzle game written in C.

## Features

- Classic 2048 gameplay with smooth tile movement
- Score calculation based on tile values
- Win detection (reaching 2048)
- Lose detection (no valid moves remaining)
- Undo/Back functionality
- New game option
- Random tile generation (2 or 4)

## Controls

- **L** - Move tiles left
- **R** - Move tiles right
- **U** - Move tiles up
- **D** - Move tiles down
- **B** - Back (undo last move)
- **N** - New Game (start over)
- **Q** - Quit the game

## How to Compile and Run

### On Linux/macOS:
```bash
gcc -o 2048 game.c
./2048
```

### On Windows (using MinGW or similar):
```bash
gcc -o 2048.exe game.c -lncurses
2048.exe
```

Note: The game uses `conio.h` for `getche()` function, which might require additional libraries on some systems.

## Game Rules

1. Tiles slide in the chosen direction until they hit the wall or another tile
2. When two tiles with the same number collide, they merge into one with their sum
3. After each valid move, a new tile (either 2 or 4) appears in a random empty spot
4. The game ends when you create a 2048 tile (win) or when there are no valid moves left (lose)

## Code Structure

- `main()` - Main game loop
- `printBoard()` - Displays the game board
- `calculateScore()` - Calculates current score
- `addRandom()` - Adds random tile to board
- `initializeBoard()` - Sets up initial game state
- `moveLeft()/Right()/Up()/Down()` - Handles tile movements
- `rotate_array()` - Rotates board for movement calculations
- `win_or_not()` - Checks for win condition
- `lose_or_not()` - Checks for lose condition

## Requirements

- C Compiler (GCC, Clang, or similar)
- Standard C libraries
- `conio.h` library (included in most Windows compilers, alternatives needed for Unix-like systems)

## Notes

- The game board is 4x4 by default (can be changed by modifying the `#define n 4`)
- Random number generation is seeded with current time
- Score is the sum of all tiles on the board
- The "Back" feature only goes back one move

## Future Improvements

Potential enhancements for this project:
- Add color to the console output
- Implement a high score system
- Add difficulty levels
- Create a graphical interface
- Add animations for tile movements

## Author

C implementation of the 2048 game. Original game concept by Gabriele Cirulli.

## License

This project is open source and available for educational purposes.
