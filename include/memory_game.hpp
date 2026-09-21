#pragma once

#include "linked_list.hpp"

class MemoryGame {
private:
    LinkedList cards;
    int rows;
    int cols;
    int firstFlipIndex;
    int secondFlipIndex;

    void initializeDeck();
    void shuffleDeck();

public:
    MemoryGame(int rows = 4, int cols = 4);

    bool flipCard(int row, int col);
    bool checkMatch();
    bool allMatched();

    void displayTerminal();
    void displayTerminalNcurses();
    void runSFML();
};