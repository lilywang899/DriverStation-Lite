/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _CONSOLE_DS_JOYSTICKS_H
#define _CONSOLE_DS_JOYSTICKS_H

#ifdef __cplusplus
extern "C" {
#endif

extern void init_joysticks(void);
extern void close_joysticks(void);
extern void update_joysticks(void);

#ifdef __cplusplus
}
#endif

#endif
