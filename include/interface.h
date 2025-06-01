/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _CONSOLE_DS_INTERFACE_H
#define _CONSOLE_DS_INTERFACE_H

#ifdef __cplusplus
extern "C" {
#endif

extern void init_interface(void);
extern void close_interface(void);
extern void update_interface(void);
extern void update_status_label(void);

extern void set_can(const int can);
extern void set_cpu(const int cpu);
extern void set_ram(const int ram);
extern void set_disk(const int disk);
extern void set_enabled(const int enabled);
extern void set_robot_code(const int code);
extern void set_robot_comms(const int comms);
extern void set_voltage(const double voltage);
extern void set_has_joysticks(const int joysticks);
extern void set_console_msg(const char *msg);

#ifdef __cplusplus
}
#endif

#endif
