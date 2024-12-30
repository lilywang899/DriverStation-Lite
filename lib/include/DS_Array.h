/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_ARRAY_H
#define _LIB_DS_ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

typedef struct _array
{
   size_t used;
   size_t size;
   void **data; //type void means you don't know the actual type of the variable your double pointer is pointing to
} DS_Array;

extern void DS_ArrayFree(DS_Array *array);
extern void DS_ArrayInsert(DS_Array *array, void *element);
extern void DS_ArrayInit(DS_Array *array, size_t initial_size);

#ifdef __cplusplus
}
#endif

#endif
