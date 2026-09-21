#include "memory_game.hpp"
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <ncurses.h>
#include <SFML/Graphics.hpp>

using namespace std;

MemoryGame::MemoryGame(int rows, int cols)
    : rows(rows),
      cols(cols),
      firstFlipIndex(-1),
      secondFlipIndex(-1) {

    initializeDeck();
    shuffleDeck();
}

void MemoryGame::initializeDeck() {
    char values[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

    for (char value : values) {
        cards.insert(Card(value));
        cards.insert(Card(value));
    }
}

void MemoryGame::shuffleDeck() {
    vector<Card> temp;

    for (int i = 0; i < cards.size(); i++) {
        temp.push_back(cards.getAt(i));
    }

    random_device rd;
    mt19937 generator(rd());

    shuffle(temp.begin(), temp.end(), generator);

    while (cards.size() > 0) {
        cards.removeAt(0);
    }

    for (Card card : temp) {
        cards.insert(card);
    }
}

bool MemoryGame::flipCard(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;
    }

    int index = row * cols + col;
    Card& card = cards.getAt(index);

    if (card.isFaceUp || card.isMatched) {
        return false;
    }

    card.isFaceUp = true;

    if (firstFlipIndex == -1) {
        firstFlipIndex = index;
        return false;
    }

    secondFlipIndex = index;
    return true;
}

bool MemoryGame::checkMatch() {
    if (firstFlipIndex == -1 || secondFlipIndex == -1) {
        return false;
    }

    Card& firstCard = cards.getAt(firstFlipIndex);
    Card& secondCard = cards.getAt(secondFlipIndex);

    if (firstCard.value == secondCard.value) {
        firstCard.isMatched = true;
        secondCard.isMatched = true;
    } else {
        firstCard.isFaceUp = false;
        secondCard.isFaceUp = false;
    }

    firstFlipIndex = -1;
    secondFlipIndex = -1;

    return allMatched();
}

bool MemoryGame::allMatched() {
    for (int i = 0; i < cards.size(); i++) {
        if (!cards.getAt(i).isMatched) {
            return false;
        }
    }

    return true;
}


void MemoryGame::displayTerminal() {
    cout << "\nMemory Game Grid:\n\n";

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int index = r * cols + c;
            Card& card = cards.getAt(index);

            if (card.isMatched) {
                cout << "[ ] ";
            } else if (card.isFaceUp) {
                cout << "[" << card.value << "] ";
            } else {
                cout << "[*] ";
            }
        }

        cout << endl;
    }

    cout << endl;
}

void MemoryGame::displayTerminalNcurses() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLUE);
        init_pair(2, COLOR_BLACK, COLOR_WHITE);
    }

    int cursorRow = 0;
    int cursorCol = 0;

    while (!allMatched()) {
        clear();

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int index = r * cols + c;
                Card& card = cards.getAt(index);

                int x = c * 4;
                int y = r * 2;

                if (r == cursorRow && c == cursorCol) {
                    attron(A_BOLD | A_REVERSE);
                }

                if (card.isMatched) {
                    mvprintw(y, x, "[ ]");
                } else if (card.isFaceUp) {
                    if (has_colors()) {
                        attron(COLOR_PAIR(2));
                    }

                    mvprintw(y, x, "[%c]", card.value);

                    if (has_colors()) {
                        attroff(COLOR_PAIR(2));
                    }
                } else {
                    if (has_colors()) {
                        attron(COLOR_PAIR(1));
                    }

                    mvprintw(y, x, "[*]");

                    if (has_colors()) {
                        attroff(COLOR_PAIR(1));
                    }
                }

                if (r == cursorRow && c == cursorCol) {
                    attroff(A_BOLD | A_REVERSE);
                }
            }
        }

        mvprintw(rows * 2 + 1, 0,
                 "Use arrows to move, SPACE/ENTER to flip. Q to quit.");

        refresh();

        int ch = getch();

        switch (ch) {
            case KEY_UP:
                if (cursorRow > 0) {
                    cursorRow--;
                }
                break;

            case KEY_DOWN:
                if (cursorRow < rows - 1) {
                    cursorRow++;
                }
                break;

            case KEY_LEFT:
                if (cursorCol > 0) {
                    cursorCol--;
                }
                break;

            case KEY_RIGHT:
                if (cursorCol < cols - 1) {
                    cursorCol++;
                }
                break;

            case ' ':
            case '\n':
                if (flipCard(cursorRow, cursorCol)) {
                    clear();

                    for (int r = 0; r < rows; r++) {
                        for (int c = 0; c < cols; c++) {
                            int index = r * cols + c;
                            Card& card = cards.getAt(index);

                            int x = c * 4;
                            int y = r * 2;

                            if (card.isMatched) {
                                mvprintw(y, x, "[ ]");
                            } else if (card.isFaceUp) {
                                mvprintw(y, x, "[%c]", card.value);
                            } else {
                                mvprintw(y, x, "[*]");
                            }
                        }
                    }

                    refresh();
                    napms(1000);
                    checkMatch();
                }
                break;

            case 'q':
            case 'Q':
                endwin();
                return;
        }
    }

    clear();
    mvprintw(rows, 0, "You Win!");
    refresh();
    getch();

    endwin();
}

void MemoryGame::runSFML() {
    const int cellSize = 100;

    sf::RenderWindow window(
        sf::VideoMode(cols * cellSize, rows * cellSize),
        "Memory Matching Game"
    );

    sf::Font font;
    bool fontLoaded =
        font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    int firstSelected = -1;
    int secondSelected = -1;
    sf::Clock mismatchClock;
    bool waitingToCheck = false;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left &&
                !waitingToCheck) {

                int col = event.mouseButton.x / cellSize;
                int row = event.mouseButton.y / cellSize;

                if (flipCard(row, col)) {
                    secondSelected = row * cols + col;
                    waitingToCheck = true;
                    mismatchClock.restart();
                } else {
                    firstSelected = row * cols + col;
                }
            }
        }

        if (waitingToCheck &&
            mismatchClock.getElapsedTime().asSeconds() >= 1.0f) {

            checkMatch();
            firstSelected = -1;
            secondSelected = -1;
            waitingToCheck = false;
        }

        window.clear();

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                int index = r * cols + c;
                Card& card = cards.getAt(index);

                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(90.0f, 90.0f));
                rectangle.setPosition(
                    static_cast<float>(c * cellSize + 5),
                    static_cast<float>(r * cellSize + 5)
                );

                if (card.isMatched) {
                    rectangle.setFillColor(sf::Color::Transparent);
                } else if (card.isFaceUp) {
                    rectangle.setFillColor(sf::Color::White);
                } else {
                    rectangle.setFillColor(sf::Color::Blue);
                }

                window.draw(rectangle);

                if (card.isFaceUp && !card.isMatched && fontLoaded) {
                    sf::Text text;
                    text.setFont(font);
                    text.setString(string(1, card.value));
                    text.setCharacterSize(40);
                    text.setFillColor(sf::Color::Black);

                    text.setPosition(
                        static_cast<float>(c * cellSize + 35),
                        static_cast<float>(r * cellSize + 25)
                    );

                    window.draw(text);
                }
            }
        }

        window.display();

        if (allMatched()) {
            sf::sleep(sf::seconds(2));
            window.close();
        }
    }
}