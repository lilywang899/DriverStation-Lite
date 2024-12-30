/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_MAIN_H
#define _LIB_DS_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DS_Timer.h"
#include "DS_Types.h"
#include "DS_Utils.h"
#include "DS_Events.h"
#include "DS_Client.h"
#include "DS_Socket.h"
#include "DS_Protocol.h"
#include "DS_Joysticks.h"
#include "DS_DefaultProtocols.h"

extern void DS_Init(void);
extern void DS_Close(void);
extern int DS_Initialized(void);

extern char *DS_GetVersion(void);
extern char *DS_GetBuildDate(void);
extern char *DS_GetBuildTime(void);

#ifdef __cplusplus
}
#endif

#endif
