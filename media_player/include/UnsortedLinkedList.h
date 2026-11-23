
#ifndef UNSORTED_LINKED_LIST_H
#define UNSORTED_LINKED_LIST_H

#include "ItemType.h"
#include <iostream>

struct Node
{
    ItemType* item;
    Node* next;

    Node(ItemType* i)
        : item(i), next(nullptr)
    {
    }

    ~Node()
    {
        delete item;
    }
};

class UnsortedLinkedList
{
protected:
    Node* listData;
    int length;

public:
    UnsortedLinkedList()
        : listData(nullptr), length(0)
    {
    }

    virtual ~UnsortedLinkedList()
    {
        Clear();
    }

    // Prevent accidental shallow copying of owned nodes.
    UnsortedLinkedList(const UnsortedLinkedList&) = delete;
    UnsortedLinkedList& operator=(const UnsortedLinkedList&) = delete;

    virtual void Clear()
    {
        while (listData != nullptr)
        {
            Node* temp = listData;
            listData = listData->next;
            delete temp;
        }

        length = 0;
    }

    // O(1): Insert a node at the front.
    virtual void Insert(ItemType* item)
    {
        if (item == nullptr)
            return;

        Node* newNode = new Node(item);
        newNode->next = listData;
        listData = newNode;
        length++;
    }

    // O(n): Search for and remove a matching item.
    virtual bool Remove(const ItemType& item)
    {
        Node* current = listData;
        Node* previous = nullptr;

        while (current != nullptr)
        {
            if (current->item->CompareTo(item))
            {
                if (previous == nullptr)
                    listData = current->next;
                else
                    previous->next = current->next;

                delete current;
                length--;
                return true;
            }

            previous = current;
            current = current->next;
        }

        return false;
    }

    // O(n): Search the linked list.
    virtual bool IsPresent(const ItemType& item) const
    {
        Node* current = listData;

        while (current != nullptr)
        {
            if (current->item->CompareTo(item))
                return true;

            current = current->next;
        }

        return false;
    }

    // O(1): Return the stored item count.
    virtual int Length() const
    {
        return length;
    }

    virtual bool IsEmpty() const
    {
        return length == 0;
    }

    // O(n): Traverse and print every item.
    virtual void ListItems() const
    {
        if (listData == nullptr)
        {
            std::cout << "List is empty.\n";
            return;
        }

        Node* current = listData;

        while (current != nullptr)
        {
            current->item->Print(std::cout);
            std::cout << '\n';
            current = current->next;
        }
    }
};

#endif
