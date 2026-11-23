
#ifndef SORTED_LINKED_LIST_H
#define SORTED_LINKED_LIST_H

#include "UnsortedLinkedList.h"

class SortedLinkedList : public UnsortedLinkedList
{
public:
    // O(n): Find the correct sorted position and insert.
    void Insert(ItemType* item) override
    {
        if (item == nullptr)
            return;

        Node* newNode = new Node(item);

        if (listData == nullptr ||
            item->LessThan(*listData->item))
        {
            newNode->next = listData;
            listData = newNode;
        }
        else
        {
            Node* current = listData;

            while (current->next != nullptr &&
                   !item->LessThan(*current->next->item))
            {
                current = current->next;
            }

            newNode->next = current->next;
            current->next = newNode;
        }

        length++;
    }
};

#endif
