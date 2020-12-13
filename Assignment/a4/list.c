//----------------------------------------------------------
// NAME: kien mai
// STUDENT NUMBER: 7876083
// COURSE: COMP 2160, SECTION: A02
// INSTRUCTOR: Dr. Eskicioglu
// ASSIGNMENT: #4 
//
// REMARKS: linked list
//---------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static Node *head = NULL;

static Node *traverseNode = NULL;

void addNode (Node * node) {
    Node *iterator;
    
    iterator = head;

    //If empty case
    if (head == NULL) {

       head = node;
       return;
    };

    //Insert after the head
    while (iterator->next != NULL) {
       iterator = iterator->next;
    }

    //New item is greater than all items in table
    //Iterator is the tail of the table
    iterator->next = node;

    return ;
}

void removeNode (Ref id) {
    Node *iterator;
    Node *temp;

    iterator = head;
    
    //If empty table
    if (head == NULL) {
        return ;
    }

    //If head is the item
    if (id == head->id) {
        temp = head;
        head = head->next;

        free(temp);

        return ;
    };

    //If the item is after head
    while(iterator->next != NULL) {
        Node *nextCell = iterator->next;
        if (id == nextCell->id) {
            iterator-> next = nextCell->next;
            free(nextCell);
            return ;
        }

        iterator = iterator->next;
    }

    //Not found item
    return;
}

void clearList () {
    Node* iterator;
    Node* temp;

    iterator = head;

    while (iterator != NULL) {
        temp = iterator;
        iterator = iterator->next;

        free(temp);
    }

    head = NULL;
}

Node *getNode (Ref id) {
    Node *iterator;
    iterator = head;

    while (iterator != NULL) {
        if (id == iterator->id) {
            
            return iterator;
        }
        iterator = iterator->next;
    } 

    //Not found item
    return NULL;
}

Node *nextNode () {

    if (head == NULL) {
        return NULL;
    };

    if (traverseNode == NULL) {
        traverseNode = head;

        return traverseNode;
    }; 

    if (traverseNode->next == NULL) {
        traverseNode = NULL;
        return NULL;
    }

    traverseNode = traverseNode->next;

    if (traverseNode == NULL) {
        return NULL;
    } else {
        return traverseNode;
    }


}

bool isListEmpty () {
    if (head == NULL) {
        return true;
    } else {
        return false;
    }
}

