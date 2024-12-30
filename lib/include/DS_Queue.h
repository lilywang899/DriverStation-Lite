/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_QUEUE_H
#define _LIB_DS_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _queue
{
   int count;
   int capacity;
   int item_size;

   int rear;
   int front;

   void **buffer;
} DS_Queue;

extern int DS_QueuePop(DS_Queue *queue);
extern void DS_QueueFree(DS_Queue *queue);
extern void *DS_QueueGetFirst(DS_Queue *queue);
extern void DS_QueuePush(DS_Queue *queue, void *item);
extern void DS_QueueInit(DS_Queue *queue, int initial_count, int item_size);

#ifdef __cplusplus
}
#endif

#endif
