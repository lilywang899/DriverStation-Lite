/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#ifndef _LIB_DS_DEFAULT_PROTOCOLS_H
#define _LIB_DS_DEFAULT_PROTOCOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "DS_Protocol.h"

extern DS_Protocol DS_GetProtocolFRC_2014(void);
extern DS_Protocol DS_GetProtocolFRC_2015(void);
extern DS_Protocol DS_GetProtocolFRC_2016(void);
extern DS_Protocol DS_GetProtocolFRC_2020(void);

#ifdef __cplusplus
}
#endif

#endif
