/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#include "DS_Utils.h"
#include "DS_Queue.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

/**
 * Removes the first item in the given \a queue
 *
 * \param queue the queue in which to operate
 * \returns \c 1 on success, \c 0 on failure
 */
extern int DS_QueuePop(DS_Queue *queue)
{
   /* Check arguments */
   assert(queue);

   /* There are no items on the queue */
   if (queue->count <= 0)
      return 0;

   /* Update queue properties */
   --queue->count;
   ++queue->front;

   /* This is a circular queue, go back to the beginning */
   if (queue->front >= queue->capacity)
      queue->front = 0;

   return 1;
}

/**
 * Resets the properties of the given \a queue and de-allocates the memory
 * used by the queue's elements
 *
 * \param queue the queue to destroy
 */
extern void DS_QueueFree(DS_Queue *queue)
{
   /* Check arguments */
   assert(queue);

   /* Free all the items in the queue */
   int element;
   for (element = 0; element < queue->capacity; ++element)
      DS_FREE(queue->buffer[element]);

   /* Delete the buffer */
   DS_FREE(queue->buffer);

   /* Reset queue properties */
   queue->rear = -1;
   queue->count = 0;
   queue->front = 0;
   queue->capacity = 0;
   queue->item_size = 0;
}

/**
 * Returns the first elemenent of the given \a queue
 *
 * \param queue the queue from which to get the first item_size
 * \returns the first element of the given \a queue, on failure, this
 *          function shall return a \c NULL pointer
 */
void *DS_QueueGetFirst(DS_Queue *queue)
{
   /* Check arguments */
   assert(queue);

   /* There are no items on the queue */
   if (queue->count <= 0)
      return NULL;

   /* Get the first item in the list */
   assert(queue->buffer);
   return (void *)queue->buffer[queue->front];
}

/**
 * Adds the given \a item to the \a queue in a circular fashion
 *
 * \param queue the queue in which to operate
 * \param item the item to add, to avoid potential errors, the pointer data
 *        is duplicated by this function
 */
void DS_QueuePush(DS_Queue *queue, void *item)
{
   /* Check arguments */
   assert(queue);

   /* Queue is full, expand it */
   if (queue->count >= queue->capacity)
   {
      queue->capacity *= 2;
      queue->buffer = (void **)realloc(queue->buffer, queue->capacity * queue->item_size);

      int i;
      for (i = queue->count; i < queue->capacity; ++i)
         queue->buffer[i] = (void **)malloc(queue->item_size);
   }

   /* Update queue properties */
   ++queue->rear;
   ++queue->count;

   /* Front item should be somewhere in the middle by now */
   if (queue->rear >= queue->capacity)
      queue->rear = 0;

   /* Since we don't want to depend on other people, copy the data */
   assert(queue->buffer);
   memcpy(queue->buffer[queue->rear], item, queue->item_size);
}

/**
 * Initializes the given queue and allocates memory for its elements
 *
 * \param queue the queue to initialize
 * \param initial_count the initial number of elements of the queue
 * \param item_size the size to use for each individual element of the queue
 */
void DS_QueueInit(DS_Queue *queue, int initial_count, int item_size)
{
   /* Set initial navigation values */
   queue->rear = -1;
   queue->count = 0;
   queue->front = 0;

   /* Set queue properties */
   queue->item_size = item_size;
   queue->capacity = initial_count;

   /* Initialize the pointer list */
   queue->buffer = (void **)calloc(initial_count, initial_count * item_size);

   /* Initialize each item in the list */
   int item;
   for (item = 0; item < initial_count; ++item)
      queue->buffer[item] = malloc(item_size); //size of DS_event so the queue fits 50 events
}
