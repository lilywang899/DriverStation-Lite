/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#include "LibDS.h"
#include "DS_Config.h"
#include "spdlog/spdlog.h"
#include "spdlog/cfg/env.h"
#include "spdlog/fmt/ostr.h"
static int init = 0;

/**
 * Initializes all the modules of the LibDS library, you should call this
 * function before your application begins interacting with the different
 * modules of the LibDS.
 */
void DS_Init(void)
{
   if (!DS_Initialized())
   {
      init = 1;
      Timers_Init(); //sets running to true and timers to a ds_array with data size of 10
      Client_Init(); //sets status string, the three different addresses to 0.0.0.0, sets ds_string game_data to 0s
      Events_Init(); //Initializes the event queue with an initial support for 50 events
      Sockets_Init(); //only for windows
      Joysticks_Init(); //another ds_array with data of 6 blocks of 0s
      Protocols_Init();
   }
}

/**
 * Closes all the modules of the LibDS library, you should call this before
 * exiting your application. Failure to do this may result with socket
 * problems (regardless if you are using the offical DS or not), memory
 * problems and increased CPU usage (due to threads managed by the LibDS)
 */
void DS_Close(void)
{
   if (DS_Initialized())
   {
      init = 0;

      Timers_Close();
      Sockets_Close();
      Protocols_Close();
      Joysticks_Close();

      Events_Close();
      Client_Close();
   }
}

/**
 * Returns \c 1 if the DS is initialized, \c 0 if not
 */
int DS_Initialized(void)
{
   return init;
}

/**
 * Returns the current version of LibDS
 * This is defined in the source to avoid reporting wrong versions when
 * importing LibDS as a library (e.g. a DLL) and using non-corresponding
 * header files
 */
char *DS_GetVersion(void)
{
   return "2.2.1";
}

/**
 * Returns the date when the library was compiled
 */
char *DS_GetBuildDate(void)
{
   return __DATE__;
}

/**
 * Returns the time when the library was compiled
 */
char *DS_GetBuildTime(void)
{
   return __TIME__;
}
