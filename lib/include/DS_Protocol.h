/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_PROTOCOL_H
#define _LIB_DS_PROTOCOL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DS_Socket.h"
#include "DS_String.h"

typedef struct _protocol
{
   DS_String name;
   DS_String (*fms_address)(void);
   DS_String (*radio_address)(void);
   DS_String (*robot_address)(void);

   DS_String (*create_fms_packet)(void);
   DS_String (*create_radio_packet)(void);
   DS_String (*create_robot_packet)(void);

   int (*read_fms_packet)(const DS_String *);
   int (*read_radio_packet)(const DS_String *);
   int (*read_robot_packet)(const DS_String *);

   void (*reset_fms)(void);
   void (*reset_radio)(void);
   void (*reset_robot)(void);

   void (*reboot_robot)(void);
   void (*restart_robot_code)(void);

   int fms_interval;
   int radio_interval;
   int robot_interval;

   int max_joysticks;
   int max_axis_count;
   int max_hat_count;
   int max_button_count;
   float max_battery_voltage;

   DS_Socket fms_socket;
   DS_Socket radio_socket;
   DS_Socket robot_socket;
   DS_Socket netconsole_socket;
} DS_Protocol;

extern void Protocols_Init();
extern void Protocols_Close();
extern void DS_ConfigureProtocol(const DS_Protocol *ptr);

extern unsigned long DS_SentFMSBytes();
extern unsigned long DS_SentRadioBytes();
extern unsigned long DS_SentRobotBytes();

extern unsigned long DS_ReceivedFMSBytes();
extern unsigned long DS_ReceivedRadioBytes();
extern unsigned long DS_ReceivedRobotBytes();

extern int DS_SentFMSPackets();
extern int DS_SentRadioPackets();
extern int DS_SentRobotPackets();

extern int DS_ReceivedFMSPackets();
extern int DS_ReceivedRadioPackets();
extern int DS_ReceivedRobotPackets();

extern void DS_ResetFMSPackets();
extern void DS_ResetRadioPackets();
extern void DS_ResetRobotPackets();

extern DS_Protocol *DS_CurrentProtocol();

#ifdef __cplusplus
}
#endif

#endif
