/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_TIMER_H
#define _LIB_DS_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <pthread.h>

/**
 * Represents a tiemr and its properties
 */
typedef struct _timer
{
   int time; /**< The time to wait until the timer expires */
   int expired; /**< Set to \c 1 if \a elapsed is greater than \a time */
   int enabled; /**< Enabled state of the timer */
   int elapsed; /**< Number of milliseconds elapsed since last reset */
   int precision; /**< The update interval (in milliseconds) */
   int initialized; /**< Set to \c 1 if the timer has been initialized */
} DS_Timer;

extern void Timers_Init(void);
extern void Timers_Close(void);
extern void DS_Sleep(const int millisecs);
extern void DS_TimerStop(DS_Timer *timer);
extern void DS_TimerStart(DS_Timer *timer);
extern void DS_TimerReset(DS_Timer *timer);
extern void DS_TimerInit(DS_Timer *timer, const int time, const int precision);

#ifdef __cplusplus
}
#endif

#endif
