/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#include "DS_Array.h"
#include "DS_Utils.h"

#include <assert.h>

/**
 * Deallocates the memory used to store the \a array data and resets the
 * properties of the given \a array
 *
 * \param array the array object to free
 */
void DS_ArrayFree(DS_Array *array)
{
   /* Check arguments */
   assert(array);
   assert(array->data);

   /* De-allocate array data */
   if (array->size > 0)
   {
      int i;
      for (i = 0; i < (int)array->size; ++i)
         DS_FREE(array->data[i]);

      DS_FREE(array->data);
   }

   /* Update array properties */
   array->used = 0;
   array->size = 0;
}

/**
 * Inserts the given \a element in the \a array. If there is no memory left
 * in the array, then this function will float the size of the array and
 * insert the item.
 *
 * \param array the array object in which to insert the given element
 * \param element pointer to the item to register with the array
 */
void DS_ArrayInsert(DS_Array *array, void *element)
{
   /* Check arguments */
   assert(array);
   assert(array->data);

   /* Resize array if required */
   if (array->used == array->size)
   {
      array->size *= 2;
      array->data = realloc(array->data, array->size);
   }

   /* Insert element */
   array->data[array->used++] = element;
}

/**
 * Initializes the data list and properties of the given \a array
 *
 * \param array the array to initialize
 * \param initial_size the initial size of the array, since the array is an
 *        array of pointers, the initial size can also be thought as the
 *        initial number of supported items
 */
void DS_ArrayInit(DS_Array *array, size_t initial_size) //array is pointer to the timer of struct _array defined in DS_array
{
   /* Check arguments */
   assert(array); //assert that it's not null

   /* Allocate array data */
   array->data = calloc(initial_size, sizeof(void *)); //dynamically allocate blocks of memory of pointers of any type

   /* Update array data */
   array->used = 0;
   array->size = initial_size;
}
