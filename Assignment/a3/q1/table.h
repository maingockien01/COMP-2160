#ifndef _TABLE_H
#define _TABLE_H

//-----------------------------------------------------------------------------
// CONSTANTS AND TYPES
//-----------------------------------------------------------------------------

typedef enum BOOL { false, true } Boolean;
typedef struct Cell cell;

//-----------------------------------------------------------------------------
// PROTOTYPES
//-----------------------------------------------------------------------------

// add an element to the table
// Return TRUE if the item is in the table
// Return FALSE if the item is *not* in the table
Boolean insertItem( int item );
// removes the int from the table
Boolean removeItem( int item );
// empty the table so that we clear all memory and can start a fresh table
void clearTable( );
// tells us whether or not the given item is in the table
Boolean search( int item );
// table iterators
// Return TRUE if item was assigned
// Return FALSE if item was *not* assigned
Boolean firstItem( int * const item );
Boolean nextItem( int * const item );

#endif
