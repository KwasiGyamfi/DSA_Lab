#include "linked_list.hpp"
using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    length = 0;
}

LinkedList::~LinkedList() {
    Node* current = head;

    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void LinkedList::insert(Card card) {
    Node* newNode = new Node(card);

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;

        while (current->next != nullptr) {
            current = current->next;
        }

        current->next = newNode;
    }

    length++;
}

Card& LinkedList::getAt(int index) {
    if (index < 0 || index >= length) {
        throw out_of_range("Invalid index");
    }

    Node* current = head;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current->data;
}

void LinkedList::removeAt(int index) {
    if (index < 0 || index >= length) {
        return;
    }

    if (index == 0) {
        Node* temp = head;
        head = head->next;
        delete temp;
    } else {
        Node* previous = head;

        for (int i = 0; i < index - 1; i++) {
            previous = previous->next;
        }

        Node* temp = previous->next;
        previous->next = temp->next;
        delete temp;
    }

    length--;
}

int LinkedList::size() const {
    return length;
}