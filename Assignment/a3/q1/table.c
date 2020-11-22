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
    cell* newCell = (cell*) malloc(sizeof(cell)) ;
    newCell->item = item;
    newCell->next = NULL;

    if (head == NULL) {
       head = newCell;
       return true;
    };

    if (item < head->item) {
        
        newCell->next = head;
        head = newCell;
        
        return true;
    }

    cell *iterator;
    iterator = head;

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
    
    if (head == NULL) {
        return false;
    }

    if (item == head->item) {
        temp = head;
        head = head->next;

        free(temp);

        return true;
    };

    while(iterator->next != NULL) {
        cell *nextCell = iterator->next;
        if (item == nextCell->item) {
            iterator-> next = nextCell->next;
            free(nextCell);
            return true;
        }

        iterator = iterator->next;
    }

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
    return false;
}

Boolean firstItem(int * item) {
    if (item == NULL) {
        return false;
    };
    if (head != NULL) {

        int firstItem = head->item;
        *item = firstItem;

        return true;
    };
    return false;
}

Boolean nextItem(int * item) {
    if (item == NULL) {
        return false;
    }
    if (head == NULL) {
        return false;
    };
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

