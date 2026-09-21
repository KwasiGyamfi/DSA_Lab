# Memory Matching Card Game Using an Unsorted Linked List

## Overview

This project implements a 4x4 memory matching card game in C++. The deck contains 16 cards consisting of eight matching pairs labeled A through H.

The cards are stored in an unsorted singly linked list rather than an array or vector. The game allows the player to reveal two cards at a time. Matching cards are marked as matched, while non-matching cards are flipped back over.

The project contains three display approaches:

1. Standard terminal output using `cout`
2. Interactive terminal interface using ncurses
3. Graphical interface using SFML

The default program uses the ncurses interface.

## Data Structure

The card deck is stored using a singly linked list.

Each node contains:

- A `Card` object
- A pointer to the next node

The linked list supports:

- Inserting cards
- Accessing a card by index
- Removing cards
- Traversing the list
- Tracking the number of cards

Because linked lists do not provide direct random access, accessing a card at a particular index requires traversing the list from the head. Therefore, `getAt()` has O(n) time complexity.

For a small 16-card game this is acceptable, although an array or vector would generally be more efficient for a grid-based game.

## Card Representation

Each card stores:

- `value` - the letter on the card
- `isFaceUp` - whether the card is currently visible
- `isMatched` - whether the card has already been matched

The deck contains two cards for each letter from A through H.

## Shuffling

The cards are copied from the linked list into a temporary `vector`.

The C++ `shuffle()` algorithm and random number generator are then used to randomize the cards.

After shuffling, the linked list is rebuilt using the randomized card order.

## Terminal Mode

The basic terminal implementation displays:

- `[*]` for hidden cards
- `[A]` through `[H]` for visible cards
- `[ ]` for matched cards

The player selects cards using row and column coordinates.

## ncurses Mode

The ncurses version provides a more interactive terminal interface.

Controls:

- Arrow keys: move between cards
- Space or Enter: flip the selected card
- Q: quit the game

ncurses allows the program to update specific locations in the terminal, process keyboard input directly, and use terminal colors.

Compared with normal `cout`, ncurses provides a better interactive experience but requires additional setup and linking.

## SFML Mode

SFML provides a graphical version of the memory game.

The SFML implementation:

- Opens a graphical game window
- Draws the 4x4 card grid
- Handles mouse input
- Displays card values when cards are face-up
- Hides matched cards
- Briefly displays both selected cards before checking a match

The SFML implementation compiles successfully in the GitHub Codespaces environment. However, GitHub Codespaces does not provide the X11 graphical display required to open the SFML window directly. The ncurses version can be run normally in the Codespaces terminal.

## Build Instructions

### Dependencies

The project requires:

- C++17 compiler
- CMake
- ncurses
- SFML

On Ubuntu, the required libraries can be installed with:

```bash
sudo apt update
sudo apt install libncurses-dev libsfml-dev