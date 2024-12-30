/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_EVENTS_H
#define _LIB_DS_EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "DS_Types.h"

/**
 * \brief The types of events that can be delivered.
 */
typedef enum
{
   DS_NULL_EVENT = 0x00,
   DS_FMS_COMMS_CHANGED = 0x01,
   DS_RADIO_COMMS_CHANGED = 0x03,
   DS_JOYSTICK_COUNT_CHANGED = 0x05,
   DS_NETCONSOLE_NEW_MESSAGE = 0x06,
   DS_ROBOT_ENABLED_CHANGED = 0x07,
   DS_ROBOT_MODE_CHANGED = 0x09,
   DS_ROBOT_REBOOTED = 0x0a,
   DS_ROBOT_COMMS_CHANGED = 0x0b,
   DS_ROBOT_CODE_CHANGED = 0x0d,
   DS_ROBOT_CODE_RESTARTED = 0x10,
   DS_ROBOT_VOLTAGE_CHANGED = 0x11,
   DS_ROBOT_CAN_UTIL_CHANGED = 0x12,
   DS_ROBOT_CPU_INFO_CHANGED = 0x13,
   DS_ROBOT_RAM_INFO_CHANGED = 0x14,
   DS_ROBOT_DISK_INFO_CHANGED = 0x15,
   DS_ROBOT_STATION_CHANGED = 0x16,
   DS_ROBOT_ESTOP_CHANGED = 0x17,
   DS_STATUS_STRING_CHANGED = 0x18,
} DS_EventType;

/**
 * \brief FMS event fields
 */
typedef struct
{
   DS_EventType type;
   int connected;
} DS_FMSEvent;

/**
 * \brief Radio event fields
 */
typedef struct
{
   DS_EventType type;
   int connected;
} DS_RadioEvent;

/**
 * \brief Robot event fields
 */
typedef struct
{
   DS_EventType type;
   int code;
   int enabled;
   int can_util;
   int cpu_usage;
   int ram_usage;
   int estopped;
   int connected;
   int disk_usage;
   float voltage;
   DS_ControlMode mode;
} DS_RobotEvent;

/**
 * \brief Joystick event fields
 */
typedef struct
{
   DS_EventType type;
   int count;
} DS_JoystickEvent;

/**
 * \brief NetConsole event fields
 */
typedef struct
{
   DS_EventType type;
   char *message;
} DS_NetConsoleEvent;

/**
 * \brief General event structure
 */
typedef union
{
   DS_EventType type;
   DS_FMSEvent fms;
   DS_RobotEvent robot;
   DS_RadioEvent radio;
   DS_JoystickEvent joystick;
   DS_NetConsoleEvent netconsole;
} DS_Event;

extern void Events_Init(void);
extern void Events_Close(void);
extern void DS_AddEvent(DS_Event *event);
extern int DS_PollEvent(DS_Event *event);

#ifdef __cplusplus
}
#endif

#endif
