#ifndef _MY_OBJECT_H
#define _MY_OBJECT_H

#include <stdio.h>

#include "ObjectManager.h"

// NOTE: we can only reference "objects". i.e. they must be structs that can be accessed.
// This way we don't have to worry about interpreting the data we manage, the user will handle it.
// We will not be handling the dynamic creation of objects since that's not required when we have garbage collection.

template<class T> class Object
{
private:
  // reference to our object in memory
  Ref ref;
  
public:
  // This function will allocate and create an object. The data must be set using operator->.
  // If there isn't enough room, garbage collection will be initiated. An error message will be printed
  // there's still no room following the collection.
  Object();
  
  // This function will guarantee that the reference to our object is removed when we go out of context.
  // This will occur when we exit a function -- this object disappears and hence our reference.
  ~Object();
  
  // This function allows you to access (read/write) the contents of a given object.
  // It returns a void pointer to the data so you can dereference it to get at your data.
  // NEVER trust this pointer, it may change for future accesses.
  T* operator->();
  
  // These functions allows us to control the updating of object references.
  // The passed reference is used to assign the target a new value. Note that this is always a controlled shallow copy.
  // If the object is updated to NULL then we remove the reference to it. In any case, the old reference is lost.
  // We have the return value since in code we're assigning to the left hand object...
  // We will also assume that assignments are always between the same types, although the compile will catch this...
  Object<T>& operator=( Object<T>& source );
  // Used to set the reference to NULL (and only NULL)
  Object<T>& operator=( int source );
};

// Note that this would normally be in a .cpp file but they're put here for easier distribution.
// This function will allocate and create an object.
template<class T> Object<T>::Object()
{
  ref = insertObject( sizeof(T) );
}

// This function will force the removal of our reference to the relevant data
template<class T> Object<T>::~Object<T>()
{
  // tell our memory that our reference is going away
  dropReference( ref );
}

// This function allows you to access the contents of a given object.
// It returns a void pointer to the data so you can dereference it to get at your data.
// NEVER trust this pointer, it may change for future accesses.
template<class T> T* Object<T>::operator->()
{
  T *rc = NULL;
  
  rc = (T *)retrieveObject( ref );
  
  return rc;
}

// This function allows us to control the updating of object references.
// The passed object is used to assign the target a new reference.
// The old reference is lost, just like Java. Thus this becomes a shallow copy.
// We have the return value since in code we're assigning to the left hand Reference...
// NOTE: we have to have a reference parameter, otherwise it deletes the temporary object
// which fires our destructor and removes our reference.
template<class T> Object<T>& Object<T>::operator=( Object<T>& source )
{
  // tell our memory that our current reference is going away
  dropReference( ref );
  
  ref = source.ref;
  
  // tell our memory that we have another reference to the source object
  addReference( ref );
  
  return *this;
}

// If the object is updated to NULL then we remove the reference to it.
template<class T> Object<T>& Object<T>::operator=( int source )
{
  // only allow a value of NULL to kill our reference
  if ( !source )
  {
    // tell our memory that our reference is going away
    dropReference( ref );
    
    ref = source;
  }
  
  return *this;
}

#endif
