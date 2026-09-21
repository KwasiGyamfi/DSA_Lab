#pragma once

#include "card.hpp"
#include <stdexcept>

struct Node {
    Card data;
    Node* next;

    Node(Card c)
        : data(c), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int length;

public:
    LinkedList();
    ~LinkedList();

    void insert(Card card);
    Card& getAt(int index);
    void removeAt(int index);
    int size() const;
};