/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_CLIENT_H
#define _LIB_DS_CLIENT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DS_Types.h"

/* Init/Close functions */
extern void Client_Init(void);
extern void Client_Close(void);

/* User-set addresses */
extern char *DS_GetCustomFMSAddress(void);
extern char *DS_GetCustomRadioAddress(void);
extern char *DS_GetCustomRobotAddress(void);

/* Protocol-set addresses */
extern char *DS_GetDefaultFMSAddress(void);
extern char *DS_GetDefaultRadioAddress(void);
extern char *DS_GetDefaultRobotAddress(void);

/* Used addresses */
extern char *DS_GetAppliedFMSAddress(void);
extern char *DS_GetAppliedRadioAddress(void);
extern char *DS_GetAppliedRobotAddress(void);

/* Game data */
extern char *DS_GetGameData(void);

/* Status string */
extern char *DS_GetStatusString(void);

/* Getters */
extern int DS_GetTeamNumber(void);
extern int DS_GetRobotCode(void);
extern int DS_GetCanBeEnabled(void);
extern int DS_GetRobotEnabled(void);
extern int DS_GetRobotCPUUsage(void);
extern int DS_GetRobotRAMUsage(void);
extern int DS_GetRobotDiskUsage(void);
extern float DS_GetRobotVoltage(void);
extern DS_Alliance DS_GetAlliance(void);
extern DS_Position DS_GetPosition(void);
extern int DS_GetEmergencyStopped(void);
extern int DS_GetFMSCommunications(void);
extern int DS_GetRadioCommunications(void);
extern int DS_GetRobotCommunications(void);
extern int DS_GetRobotCANUtilization(void);
extern DS_ControlMode DS_GetControlMode(void);
extern float DS_GetMaximumBatteryVoltage(void);

/* Setters */
extern void DS_RebootRobot(void);
extern void DS_RestartRobotCode(void);
extern void DS_SetGameData(const char *data);
extern void DS_SetTeamNumber(const int team);
extern void DS_SetRobotEnabled(const int enabled);
extern void DS_SetEmergencyStopped(const int stop);
extern void DS_SetAlliance(const DS_Alliance alliance);
extern void DS_SetPosition(const DS_Position position);
extern void DS_SetControlMode(const DS_ControlMode mode);
extern void DS_SetCustomFMSAddress(const char *address);
extern void DS_SetCustomRadioAddress(const char *address);
extern void DS_SetCustomRobotAddress(const char *address);
extern void DS_SendNetConsoleMessage(const char *message);

#ifdef __cplusplus
}
#endif

#endif
