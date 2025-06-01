/*
 * The Driver Station Library (LibDS)
 * Copyright (c) Lily Wang, Alex Spataru and other contributors.
 * Open Source Software; you can modify and/or share it under the terms of
 * the MIT license file in the root directory of this project.
 */

#include "DS_Array.h"
#include "DS_Config.h"
#include "DS_Events.h"
#include "DS_Joysticks.h"
#include "../../src/interface.c"
#include <curses.h>
#include "SDL3/SDL.h"
#include <stdio.h>

/**
 * Represents a joystick and its information
 */
typedef struct _joystick
{
   int *hats; /**< An array with the hat angles */
   float *axes; /**< An array with the axis values */
   int *buttons; /**< An array with the button states */
   int num_axes; /**< The number of axes of the joystick */
   int num_hats; /**< The number of hats of the joystick */
   int num_buttons; /**< The number of buttons of the joystick */
} DS_Joystick;

/**
 * Holds all the joysticks
 */
static DS_Array array;

/**
 * Registers a joystick event to the LibDS event system
 */
static void register_event()
{
   DS_Event event;
   event.joystick.count = DS_GetJoystickCount();
   event.joystick.type = DS_JOYSTICK_COUNT_CHANGED;
   DS_AddEvent(&event);
}

/**
 * Returns the joystick structure at the given index
 * If the joystick does not exist, this function shall return \c NULL
 */
static DS_Joystick *get_joystick(int joystick)
{
   if ((int)array.used >= joystick)
      return (DS_Joystick *)array.data[joystick];

   return NULL;
}

/**
 * Returns \c true if the given \a joystick exists and is valid
 */
static int joystick_exists(int joystick)
{
   if (DS_GetJoystickCount() >= joystick)
      return get_joystick(joystick) != NULL;

   return 0;
}

/**
 * Initializes the joystick array, with an initial support for 6 joysticks
 */
void Joysticks_Init(void)
{
   DS_ArrayInit(&array, 6);
}

/**
 * De-allocates the joystick array data
 */
void Joysticks_Close(void)
{
   DS_ArrayFree(&array);
   register_event();
}

/**
 * Returns the number of joysticks registered with the LibDS
 */
int DS_GetJoystickCount(void)
{
   return (int)array.used;
}

/**
 * Returns the number of hats that the given \a joystick has.
 * If the joystick does not exist, this function will return \c 0
 */
int DS_GetJoystickNumHats(int joystick)
{
   if (joystick_exists(joystick))
      return get_joystick(joystick)->num_hats;

   return 0;
}

/**
 * Returns the number of axes that the given \a joystick has.
 * If the joystick does not exist, this function will return \c 0
 */
int DS_GetJoystickNumAxes(int joystick)
{
   if (joystick_exists(joystick))
      return get_joystick(joystick)->num_axes;

   return 0;
}

/**
 * Returns the number of buttons that the given \a joystick has.
 * If the joystick does not exist, this function will return \c 0
 */
int DS_GetJoystickNumButtons(int joystick)
{
   if (joystick_exists(joystick))
      return get_joystick(joystick)->num_buttons;

   return 0;
}

/**
 * Returns the value that the given \a hat in the given \a joystick has.
 * If the joystick or hat do not exist, this function will return \c 0
 *
 * \note Regardless of protocol implementation, this function will return
 *       a neutral value if the robot is disabled. This is for additional
 *       safety!
 */
int DS_GetJoystickHat(int joystick, int hat)
{
   if (CFG_GetRobotEnabled() && joystick_exists(0))
   {
      DS_Joystick *stick = get_joystick(0);
      if (stick->num_hats > hat) {
          return stick->hats[hat];
      }
   }

   return 0;
}

/**
 * Returns the value that the given \a axis in the given \a joystick has.
 * If the joystick or axis do not exist, this function will return \c 0
 *
 * \note Regardless of protocol implementation, this function will return
 *       a neutral value if the robot is disabled. This is for additional
 *       safety!
 */
float DS_GetJoystickAxis(int joystick, int axis)
{
   if (CFG_GetRobotEnabled() && joystick_exists(joystick))
   {
      DS_Joystick *stick = get_joystick(joystick);

      if (stick->num_axes > axis) {
          return stick->axes[axis];
      }
   }

   return 0;
}

/**
 * Returns the value that the given \a button in the given \a joystick has.
 * If the joystick or button do not exist, this function will return \c 0
 *
 * \note Regardless of protocol implementation, this function will return
 *       a neutral value if the robot is disabled. This is for additional
 *       safety!
 */
int DS_GetJoystickButton(int joystick, int button)
{
   if (CFG_GetRobotEnabled() && joystick_exists(0))
   {
      DS_Joystick *stick = get_joystick(0);
       
	if (stick->buttons[button]) {
               wprintw(console_win,"DS_GetJoystickButton %d, %d\n", button, stick->buttons[button]);
           }
      if (stick->num_buttons > button)
	{
         return stick->buttons[button];
   }}

   return 0;
}

/**
 * Removes all the registered joysticks from the LibDS
 */
void DS_JoysticksReset(void)
{
   DS_ArrayFree(&array);
   DS_ArrayInit(&array, 6);

   register_event();
}

/**
 * Registers a new joystick with the given number of \a axes, \a hats and
 * \a buttons. All joystick values are set to a neutral state to ensure
 * safe operation of the robot.
 */
void DS_JoysticksAdd(const int axes, const int hats, const int buttons)
{
   /* Joystick is empty */
   if (axes <= 0 && hats <= 0 && buttons <= 0)
   {
      fprintf(stderr, "DS_JoystickAdd: Cannot register empty joystick!\n");
      return;
   }

   /* Allocate memory for a new joystick */
   DS_Joystick *joystick = (DS_Joystick *)calloc(1, sizeof(DS_Joystick));

   /* Set joystick properties */
   joystick->num_axes = axes;
   joystick->num_hats = hats;
   joystick->num_buttons = buttons;

   /* Set joystick value arrays */
   joystick->hats = calloc(hats, sizeof(int));
   joystick->axes = calloc(axes, sizeof(float));
   joystick->buttons = calloc(buttons, sizeof(int));

   /* Register the new joystick in the joystick list */
   DS_ArrayInsert(&array, (void *)joystick);

   /* Emit the joystick count changed event */
   register_event();
}

/**
 * Updates the \a angle of the given \a hat in the given \a joystick
 */
void DS_SetJoystickHat(int joystick, int hat, int angle)
{
   if (joystick_exists(0))
   {
      DS_Joystick *stick = get_joystick(0);

      if (stick->num_hats > hat)
         stick->hats[hat] = angle;
   }
}

/**
 * Updates the \a value of the given \a axis in the given \a joystick
 */
void DS_SetJoystickAxis(int joystick, int axis, float value)
{
   if (joystick_exists(joystick))
   {
      DS_Joystick *stick = get_joystick(joystick);

      if (stick->num_axes > axis)
         stick->axes[axis] = value;
   }
}

/**
 * Updates the \a pressed state of the given \a button in the given \a joystick
 */
void DS_SetJoystickButton(int joystick, int button, int pressed)
{
   if (joystick_exists(0))
   {
      DS_Joystick *stick = get_joystick(0);

      if (stick->num_buttons > button){
         stick->buttons[button] = (pressed > 0) ? 1 : 0;

           if (stick->buttons[button]) {
               set_console_msg("button pressed");
               //wprintw(console_win,"button %d pressed %d\n", button, pressed);
           }
}
   }
}

/////------get from joystick.c
#define INVALID_ID -1
#define SDL_AXIS_RANGE 0x8000
/**
 * Allows the \c update_joysticks() function to know if its
 * safe to check for new SDL events
 */
static int initialized = 0;
/**
 * SDL2 does not adjust the joystick IDs with the 'real' USB
 * ID's, which causes a lot of trouble when updating the
 * joystick values with the Driver Station
 */
static int joystick_tracker = -1;
/**
 * Calculates the dynamic ID of the given joystick
 */
static int get_id(const int id)
{
    int joystick = id;
    joystick = abs(joystick_tracker - (joystick + 1));
    int  num_joysticks;
    SDL_GetJoysticks(&num_joysticks);
    if (joystick >= num_joysticks )
        joystick -= 1;
    return joystick;
}
/**
 * Registers all the detected SDL joysticks with the Driver Station
 */
static void register_joysticks(void)
{
    DS_JoysticksReset();
    int  num_joysticks;
    SDL_GetJoysticks(&num_joysticks);
    for (int i = 1; i < (num_joysticks+1); ++i)
    {
        SDL_Joystick *joystick = SDL_OpenJoystick(i);
        if (joystick)
        {
            printf("adding to ds\n");
            DS_JoysticksAdd(SDL_GetNumJoystickAxes(joystick), SDL_GetNumJoystickHats(joystick),
                            SDL_GetNumJoystickButtons(joystick));
        }
    }
}
/**
 * Extracts the hat/POV information from the given \a event
 * and updates the state of the Driver Station joysticks
 */
static void process_hat_event(SDL_Event *event) //never reset to zero, either a value or default value
{
    if (!event)
        return;
    int angle = 0;
    int hat = event->jhat.hat;
    int joystick = get_id(event->jhat.which);
    switch (event->jhat.value)
    {
        case SDL_HAT_RIGHTUP:
	    printf("rightup hat");
            angle = 45;
            break;
        case SDL_HAT_RIGHTDOWN:
	    printf("rightdown hat");
            angle = 135;
            break;
        case SDL_HAT_LEFTDOWN:
	    printf("leftdown hat");
            angle = 225;
            break;
        case SDL_HAT_LEFTUP:
	    printf("leftup  hat");
            angle = 315;
            break;
        case SDL_HAT_UP:
	    printf("hat up");
            angle = 0;
            break;
        case SDL_HAT_RIGHT:
	    printf("right hat");
            angle = 90;
            break;
        case SDL_HAT_DOWN:
	    printf("down hat");
            angle = 180;
            break;
        case SDL_HAT_LEFT:
	    printf("left  hat");
            angle = 270;
            break;
        default:
	    printf("default hat"); //case when hat is not pressed, "centered", restoring to center counts as an event
            angle = -1;
            break;
    }
    if (joystick > INVALID_ID)
        DS_SetJoystickHat(joystick, hat, angle);
}
/**
 * Extracts the axis information from the given \a event and updates
 * the state of the Driver Station joysticks
 */
static void process_axis_event(SDL_Event *event)
{
    if (!event)
        return;
    int axis = event->jaxis.axis;
    int joystick = get_id(event->jaxis.which);
    double value = ((double)(event->jaxis.value)) / SDL_AXIS_RANGE;
    if (joystick > INVALID_ID)
        DS_SetJoystickAxis(joystick, axis, value);
}
/**
 * Extracts the button information from the given \a event
 * and updates the state of the Driver Station joysticks
 */
static void process_button_event(SDL_Event *event)
{
    if (!event)
        return;
    int button = event->jbutton.button;
    int joystick = get_id(event->jbutton.which);
    int pressed = (event->jbutton.down == 1);
    if (joystick > INVALID_ID)
        DS_SetJoystickButton(joystick, button, pressed);
}
/**
 * Initializes SDL in another thread (to avoid slowing down the startup time)
 */
void init_joysticks(void)
{
    if (SDL_Init(SDL_INIT_JOYSTICK) == 1)
    {
        initialized = 1;
        SDL_SetJoystickEventsEnabled(true);
    }
    else
    {
        printf("Cannot initialize SDL!");
        exit(EXIT_FAILURE);
    }
}
/**
 * Instructs the SDL library to begin closing down
 */
void close_joysticks(void)
{
    int  num_joysticks;
    SDL_GetJoysticks(&num_joysticks);
    for (int i = 0; i < num_joysticks ; ++i) {
        SDL_CloseJoystick(SDL_OpenJoystick(i));
    }
    SDL_Quit();
}
/**
 * Queries for new SDL joystick events and updates the
 * Driver Station with the new joystick information.
 */

void update_joysticks(void)
{
    if (!initialized)
    {
        printf("failed");
        return;
    }
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_EVENT_JOYSTICK_ADDED:
                set_console_msg("Added joystick");
                //printf("joystick added! : %d\n",event.type);
                joystick_tracker++;
                register_joysticks();
                break;
            case SDL_EVENT_JOYSTICK_REMOVED:
                register_joysticks();
                break;
            case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                set_console_msg("axis motion detected");
                //printf("axis motion detected\n");
                process_axis_event(&event);
                break;
            case SDL_EVENT_JOYSTICK_HAT_MOTION:
                set_console_msg("hat pressed");
                //printf("hat pressed\n");
                process_hat_event(&event);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                set_console_msg("button pressed");
                //wprintw(console_win,"button pressed\n");
                process_button_event(&event);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_UP:
                //wprintw(console_win,"button released\n");
                set_console_msg("button released");
                process_button_event(&event);
                break;
            default:
                break;
        }
    }
}
