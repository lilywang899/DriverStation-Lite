/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_JOYSTICKS_H
#define _LIB_DS_JOYSTICKS_H

#ifdef __cplusplus
extern "C" {
#endif

extern void Joysticks_Init(void);
extern void Joysticks_Close(void);

extern int DS_GetJoystickCount(void);
extern int DS_GetJoystickNumHats(int joystick);
extern int DS_GetJoystickNumAxes(int joystick);
extern int DS_GetJoystickNumButtons(int joystick);

extern int DS_GetJoystickHat(int joystick, int hat);
extern float DS_GetJoystickAxis(int joystick, int axis);
extern int DS_GetJoystickButton(int joystick, int button);

extern void DS_JoysticksReset(void);
extern void DS_JoysticksAdd(const int axes, const int hats, const int buttons);
extern void DS_SetJoystickHat(int joystick, int hat, int angle);
extern void DS_SetJoystickAxis(int joystick, int axis, float value);
extern void DS_SetJoystickButton(int joystick, int button, int pressed);

#ifdef __cplusplus
}
#endif

#endif
