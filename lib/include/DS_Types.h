/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_TYPES_H
#define _LIB_DS_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
   DS_CONTROL_TEST,
   DS_CONTROL_AUTONOMOUS,
   DS_CONTROL_TELEOPERATED,
} DS_ControlMode;

typedef enum
{
   DS_ALLIANCE_RED,
   DS_ALLIANCE_BLUE,
} DS_Alliance;

typedef enum
{
   DS_POSITION_1,
   DS_POSITION_2,
   DS_POSITION_3,
} DS_Position;

typedef enum
{
   DS_SOCKET_UDP,
   DS_SOCKET_TCP,
} DS_SocketType;

#ifdef __cplusplus
}
#endif

#endif
