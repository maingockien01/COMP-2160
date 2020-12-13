//------------------------------------------------------
// NAME: Kien Mai
// STUDENT NUMBER: 7876083
// COURSE: COMP 2160
// INSTRUCTOR Dr. Eskicioglu
// ASSIGNMENT: #4
//
// REMARKS: ObjectManager implementation.
//------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>

#include "ObjectManager.h"
#include "list.h"

//------------------------------------------------------
// VARIABLES
//------------------------------------------------------

void *buffer;
ulong freePtr;

Ref nodeRef;

//------------------------------------------------------
// PROTOCOLS
//------------------------------------------------------

//ObjectManager hidden function
void compact ();
void destroyObject (Ref ref);

// Helpers
Ref createRef ();
Node *allocateSpace (ulong size); //Create a node 

void printObject (Node *node);

//---------------------------------------------------------------
// IMPLEMENTATIONS
//---------------------------------------------------------------

Ref insertObject(ulong size) {
    if (buffer == NULL) {
        fprintf(stderr, "ObjectManger has not been initiated\n");
        return NULL_REF;
    };

    if (size <= 0) {
        fprintf(stderr, "The size of object is invalid!\n");
        return NULL_REF;
    };
    if (freePtr + size > MEMORY_SIZE) {
        compact ();
        if (freePtr + size > MEMORY_SIZE) { 
            fprintf(stderr, "There is not enough available memory\n");
            return NULL_REF;
        };
    };

    Node *newNode = allocateSpace(size);

    if (newNode == NULL) {
        return NULL_REF;
    };
    
    addNode(newNode);
    return newNode->id;
};

void *retrieveObject(Ref ref) {
    if (buffer == NULL) {
        fprintf(stderr, "ObjectManger has not been initiated\n");
        return NULL;
    };

    if (ref == NULL_REF) {
        fprintf(stderr, "The ref input is invalid!\n");
        return NULL;
    };

    Node *node = getNode(ref);

    if (node == NULL) {
        fprintf(stderr, "Found no object matching the given ref!\n");
        return NULL;
    };

    int start = node->start;

    if (start < MEMORY_SIZE && start >= 0) {
        uchar * tempBuffer = (uchar *) buffer;
        return &(tempBuffer[start]);
    } else {
        return NULL;
    }
};

void addReference (Ref ref) {
    if (buffer == NULL) {
        fprintf(stderr, "ObjectManger has not been initiated\n");
        return ;
    };

    
    Node *node = getNode(ref);

    if (node == NULL) {
        return;
    };

    node->refCount ++;
};

void dropReference (Ref ref) {
    if (buffer == NULL) {
        fprintf(stderr, "ObjectManger has not been initiated\n");
        return ;
    };

    Node *node = getNode (ref);

    if (node == NULL) {
        return;
    };
    node->refCount --;

    if (node->refCount <= 0) {
        destroyObject(ref);
    }
};

void initPool () {
    buffer = (void *) malloc(MEMORY_SIZE * 1);

    freePtr = 0;
    nodeRef = 0;
};

void destroyPool () {
    if (buffer == NULL) {
        fprintf(stderr, "ObjectManger has not been initiated\n");
        return ;
    };

    free(buffer);
    clearList();
};

void dumpPool () {
    if (buffer == NULL) {
        fprintf(stderr, "ObjectManger has not been initiated\n");
        return ;
    };
    Node *iterator;
    iterator = nextNode ();

    fprintf(stdout, "-----Object List------\n");
    
    if (iterator == NULL) {
        fprintf(stdout, "There is no object currently in track!\n");
        return ;
    };

    fprintf(stdout, "The list of objects currently allocated:\n");

    while (iterator != NULL) {
        printObject(iterator);
        iterator = nextNode ();
    };
    
    return;
};

void compact () {
    if (buffer == NULL) {
        fprintf(stderr, "ObjectManger has not been initiated\n");
        return ;
    };
    void *secondBuffer;
    uchar *secondTempBuffer;
    uchar *tempBuffer;
    ulong secondFreePtr;
    Node *iterator;

    int i;

    int existObject = 0;
    ulong currentBytesInUse = 0;
    ulong bytesCollected = 0;

    secondFreePtr = 0;
    secondBuffer = malloc(MEMORY_SIZE);

    secondTempBuffer = (uchar *)  secondBuffer;
    tempBuffer = (uchar *) buffer;

    if (isListEmpty() == true) {
        free(buffer);
        buffer = secondBuffer;
        freePtr = 0;

        return;
    };

    iterator = nextNode ();

    while (iterator != NULL) {
        ulong size = iterator->size;
        ulong start = iterator->start;

        for (i = 0; i < size; i ++) {
            secondTempBuffer[secondFreePtr+i] = tempBuffer[start+i];
        }
        
        iterator->start = secondFreePtr;

        secondFreePtr += size;

        existObject ++;
        currentBytesInUse += size;

        iterator = nextNode ();
    }

    bytesCollected = freePtr - secondFreePtr;

    free(buffer);
    buffer = secondBuffer;
    freePtr = secondFreePtr;

    fprintf(stdout, "\nCompact:\nObjects exist: %d\nBytes in use: %lu\nBytes collected: %lu\n", existObject, currentBytesInUse, bytesCollected);

};

//Extra
void destroyObject (Ref ref) {
    Node *node = getNode(ref);

    if (node == NULL) {
        return;
    };

    removeNode(ref);
}

//Helpers
Node* allocateSpace (ulong size) {

    if (freePtr + size > MEMORY_SIZE) {
        return NULL;
    };
    if (size <= 0) {
        return NULL;
    };
    
    Node *newNode = (Node *) malloc(sizeof(Node));

    assert(newNode != NULL);

    newNode->size = size;
    newNode->start = freePtr;
    newNode->id = createRef();
    newNode->refCount = 1;
    newNode->next = NULL;

    freePtr += size;


    return newNode;
}

Ref createRef () {
    nodeRef ++;
    return nodeRef;
}

void printObject (Node * node) {
    uchar *tempBuffer = (uchar *) buffer;
    fprintf(stdout, "Object #%lu\nSize: %lu\nStart address: %p\n--------\n", node->id, node->size, &tempBuffer[node->start]);
}
