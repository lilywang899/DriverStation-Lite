/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#include "DS_Queue.h"
#include "DS_Events.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>

static DS_Queue events;

/**
 * Initializes the event queue with an initial support for 50 events
 */
void Events_Init(void)
{
   DS_QueueInit(&events, 50, sizeof(DS_Event));
}

/**
 * De-allocates the event queue (that's all)
 */
void Events_Close(void)
{
   DS_QueueFree(&events);
}

/**
 * Adds the given \a event to the event queue
 *
 * \param event the event to register in the event queue
 */
void DS_AddEvent(DS_Event *event)
{
   assert(event);
   DS_QueuePush(&events, (void *)event);
}

/**
 * Polls for currently pending events and copies the first event in the queue
 * to the given \a event object.
 *
 * \returns 1 if there are any pending events, or 0 if there are none available.
 *
 * \param event we write the obtained event data here
 */
int DS_PollEvent(DS_Event *event)
{
   DS_Event *front = (DS_Event *)DS_QueueGetFirst(&events);

   if (front)
   {
      DS_QueuePop(&events);
      memcpy(event, front, sizeof(DS_Event));
      return 1;
   }

   return 0;
}
