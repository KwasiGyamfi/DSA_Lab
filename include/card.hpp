#pragma once

struct Card {
    char value;
    bool isFaceUp;
    bool isMatched;

    Card(char val)
        : value(val), isFaceUp(false), isMatched(false) {}
};