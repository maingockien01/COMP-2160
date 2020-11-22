//----------------------------------------------------------
// NAME: kien mai
// STUDENT NUMBER: 7876083
// COURSE: COMP 2160, SECTION: A02
// INSTRUCTOR: Dr. Eskicioglu
// ASSIGNMENT: #3, QUESTION: #1
//
// REMARKS: ADT table implemented by linked list
//---------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>

#include "table.h"

struct Cell {
    cell *next;
    int item;
};

static cell *head = NULL;

static cell *traverseNode = NULL;

Boolean insertItem (int item) {
    cell *iterator;
    
    //If item is duplicating 1 item in the table
    iterator = head;
    while (iterator != NULL) {
        if (iterator-> item == item) {

            return false;
        }
        iterator = iterator->next;
    }

    //Create new cell
    cell* newCell = (cell*) malloc(sizeof(cell)) ;
    newCell->item = item;
    newCell->next = NULL;

    //If empty case
    if (head == NULL) {

       head = newCell;
       return true;
    };

    //If insert at the head
    if (item < head->item) {

        newCell->next = head;
        head = newCell;
        
        return true;
    }

    iterator = head;

    //Insert after the head
    while (iterator->next != NULL) {
        cell *nextCell = iterator->next;
        if (item < nextCell->item) {

            newCell->next = iterator->next;
            iterator->next = newCell;

            return true;
        }
        iterator = iterator->next;
    }

    iterator->next = newCell;

    return true;
}

Boolean removeItem (int item) {
    cell *iterator;
    cell *temp;
    iterator = head;
    
    //If empty table
    if (head == NULL) {
        return false;
    }

    //If head is the item
    if (item == head->item) {
        temp = head;
        head = head->next;

        free(temp);

        return true;
    };

    //If the item is after head
    while(iterator->next != NULL) {
        cell *nextCell = iterator->next;
        if (item == nextCell->item) {
            iterator-> next = nextCell->next;
            free(nextCell);
            return true;
        }

        iterator = iterator->next;
    }

    //Not found item
    return false;
}

void clearTable () {
    cell* iterator;
    cell* temp;

    iterator = head;

    while (iterator != NULL) {
        temp = iterator;
        iterator = iterator->next;

        free(temp);
    }

    head = NULL;
}

Boolean search (int item) {
    cell *iterator;
    iterator = head;

    while (iterator != NULL) {
        if (item == iterator->item) {
            
            return true;
        }
        iterator = iterator->next;
    }

    //Not found item
    return false;
}

Boolean firstItem(int * item) {
    //If item is empty 
    if (item == NULL) {
        return false;
    }

    //If table empty
    if (head == NULL) {
        return false;
    } else {

        int firstItem = head->item;
        *item = firstItem;

        return true;
    };
}


Boolean nextItem(int * item) {
    //If item is NULL
    if (item == NULL) {
        return false;
    }

    //If table is empty
    if (head == NULL) {
        return false;
    };

    //If Traverse node is empty (start from begin)
    if (traverseNode == NULL) {
        traverseNode = head;
        int next = traverseNode->item;
        *item = next;
        return true;
    } else {
        traverseNode = traverseNode->next;
        if (traverseNode != NULL) {
            int next = traverseNode->item;
            *item = next;
            return true;
        } else {
            return false;
        }
    }
    
}

