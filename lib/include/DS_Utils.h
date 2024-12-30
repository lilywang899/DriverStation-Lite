/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_UTILS_H
#define _LIB_DS_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "DS_String.h"

/*
 * You may find these useful
 */
#define DS_FallBackAddress "0.0.0.0"
#define DS_Max(a, b) ((a) > (b) ? a : b)
#define DS_Min(a, b) ((a) < (b) ? a : b)
#define DS_FREE(p)                                                                                                     \
   if (p)                                                                                                              \
   {                                                                                                                   \
      free(p);                                                                                                         \
      p = NULL;                                                                                                        \
   }

/*
 * Icon types for message boxes
 */
typedef enum
{
   DS_ICON_INFORMATION,
   DS_ICON_WARNING,
   DS_ICON_ERROR,
} DS_IconType;

/*
 * Misc functions
 */
extern uint32_t DS_CRC32(const void *buf, size_t size);
extern uint8_t DS_FloatToByte(const float val, const float max);
extern DS_String DS_GetStaticIP(const int net, const int team, const int host);
extern void DS_ShowMessageBox(const DS_String *caption, const DS_String *message, const DS_IconType icon);

#ifdef __cplusplus
}
#endif

#endif
