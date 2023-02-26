# ChessEngine
C++ chess engine

Implementation of the minimax algorithm and alpha-beta pruning

## Speed

On my machine using ubuntu, depth=4 takes less than 10 seconds per move, while depth=5 takes 10-90 seconds per move

## Strength

The engine is at the level of an intermediate player at depth=5, and at the level of a beginner at depth=4

## Move generation

Move generation is handled by the [cpp-chess library](https://github.com/pjpuzzler/cpp-chess) (chess.cpp and chess.h) which is a port of python-chess. Note that the library was slightly modified for my code to work

## Requirements

cpp-chess requires c++20, so you have to use c++20 to compile the engine.

## Usage

First of all type in the depth that the engine will use, preferably 4 or 5. Then type "white" or "black" (exact strings) so the engine knows what color you are playing with. And then type in each move you play, note that if it's illegal, the engine will crash.

### Note

There might be a glitch where if the engine's playing black, it will try to lose on purpose, but I'm not sure if it's fixed or not
