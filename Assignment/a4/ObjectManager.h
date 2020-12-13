/*
 * ObjectManager.h
 * COMP2160 Programming Practices
 *
 * Object Manager header file
 */


//This is the interface for the object manager.
//Note: The terms object and block are used interchangably below.

#ifndef _OBJECT_MANAGER_H
#define _OBJECT_MANAGER_H

// The number of bytes of memory we have access to -- put here so
// everyone's consistent.
#ifndef MEMORY_SIZE
#define MEMORY_SIZE 1024*512
#endif

#define NULL_REF 0

typedef unsigned long Ref;
typedef unsigned long ulong;
typedef unsigned char uchar;

/*
 * Note that we provide our entire interface via this object module
 * and completely hide our index (see course notes). This allows us to
 * change indexing strategies without affecting the interface to
 * everyone else.

 * This function trys to allocate a block of given size from our buffer.
 * It will fire the garbage collector as required.
 * We always assume that an insert always creates a new object...
 * On success it returns the reference number for the block of memory
 * allocated for the object.
 * On failure it returns NULL_REF (0)
 */
Ref insertObject( ulong size );

// returns a pointer to the object being requested given by the reference id
void *retrieveObject( Ref ref );

// update our index to indicate that we have another reference to the given object
void addReference( Ref ref );

// update our index to indicate that a reference is gone
void dropReference( Ref ref );

// initialize the object manager
void initPool();

// clean up the object manager (before exiting)
void destroyPool();

/*
 * This function traverses the index and prints the info in each entry
 * corresponding to a block of allocated memory. You should print the
 * block's reference id, its starting address, and its size (in
 * bytes).
 */
void dumpPool();

#endif
