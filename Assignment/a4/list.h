#ifndef _TABLE_H
#define _TABLE_H
#include "ObjectManager.h"
#include<stdbool.h>

//-----------------------------------------------------------------------------
// CONSTANTS AND TYPES
//-----------------------------------------------------------------------------

typedef struct ObjectInformation Node;

struct ObjectInformation {
    ulong start;
    ulong size;
    Ref id;
    int refCount;
    Node *next;
     
};


//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------

// add an element to the table
// Return TRUE if the item is in the table
// Return FALSE if the item is *not* in the table
void addNode(Node * node);
// removes the int from the table
void removeNode(Ref id);
// empty the table so that we clear all memory and can start a fresh table
void clearList();
// tells us whether or not the given item is in the table
Node *getNode(Ref id);

Node *nextNode ();

bool isListEmpty ();

#endif
