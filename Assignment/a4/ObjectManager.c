#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#include "ObjectManager.h"
#include "list.h"

void *buffer;
ulong freePtr;

Ref nodeRef;

//------------------------------------------------------
// PROTOCOLS
//------------------------------------------------------

void compact ();
void destroyObject (Ref ref);

// Helpers
Ref createRef ();
Node *allocateSpace (ulong size);
void clearSpace (Node * node);

void printObject (Node *node);

//---------------------------------------------------------------
// IMPLEMENTATIONS
//---------------------------------------------------------------

Ref insertObject(ulong size) {
    //Check if there is available space
    //if no: defragment
        //if still no after defragment return error
    //otherwise
    // allocate space
    if (buffer == NULL) {
        return NULL_REF;
    };

    if (size <= 0) {
        return NULL_REF;
    };
    if (freePtr + size > MEMORY_SIZE) {
        compact ();
        if (freePtr + size > MEMORY_SIZE) { 
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
        return NULL;
    };

    Node *node = getNode(ref);

    if (ref == NULL_REF) {
        return NULL;
    };

    if (node == NULL) {
        return NULL;
    };

    int start = node->start;

    if (start < MEMORY_SIZE) {
        uchar * tempBuffer = (uchar *) buffer;
        return &(tempBuffer[start]);
    } else {
        return NULL;
    }
};

void addReference (Ref ref) {
    if (buffer == NULL) {
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
    free(buffer);

    clearList();
};

void dumpPool () {
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

    bytesCollected = freePtr - currentBytesInUse;

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

    clearSpace(node);
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

void clearSpace (Node *node) {
    int i;
    for (i = 0; i < node->size; i ++) {
        //TODO: Clear byte
        //free(buffer[i+node->start]);
    }

}

Ref createRef () {
    nodeRef ++;
    return nodeRef;
}

void printObject (Node * node) {
    uchar *tempBuffer = (uchar *) buffer;
    fprintf(stdout, "Object #%lu\nSize: %lu\nStart address: %p\n--------\n", node->id, node->size, &tempBuffer[node->start]);
}
