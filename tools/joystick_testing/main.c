
#include <SDL3/SDL.h>
#include <stdio.h>

// This program opens a joystick and tells you
// when a button is pressed or an axis is moved.
// This demsontrates how to read from the joystick
// using an event-based system. In another example
// I will show how to poll the state of each button.
int main() {
    // Initialize the joystick subsystem for SDL2
    int joysticks = SDL_Init(SDL_INIT_JOYSTICK);
    printf("\"%d\"\n", joysticks);
    // If there was an error setting up the joystick subsystem, quit.
    if (joysticks < 0) {
        printf("Unable to initialize the joystick subsystem.\n");
        return -1;
    }
    // int joysticks;
    // if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) == 1)
    // {
    //     joysticks = 1;
    //     SDL_SetJoystickEventsEnabled(true);
    // }
    //
    // else
    // {
    //     printf("Cannot initialize SDL!");
    //     //exit(EXIT_FAILURE);
    // }

    // Check how many joysticks are connected.
    int count;
    if (SDL_GetJoysticks(&count) != NULL)
    {
        joysticks = count;
    }
    else
    {
        printf("failed");
        return -1;
    }
    printf("There are %d joysticks connected.\n", joysticks);

    // If there are joysticks connected, open one up for reading
    if (joysticks > 0) {
        if (SDL_OpenJoystick(1) == NULL) {
            printf("\"%s\"\n", SDL_GetError());
            printf("There was an error reading from the joystick.\n");
            return -1;
        }
    }
    // If there are no joysticks connected, exit the program.
    else {
        printf("There are no joysticks connected. Exiting...\n");
        return -1;
    }

    int quit = 0;
    SDL_Event event;

    // An infinite loop that keeps going until we set
    // the quit variable to a non-zero value. We
    // put this loop so that we can keep on listening to
    // the joystick until we are done with it.
    while (!quit) {
        // The event variable stores a list of events.
        // The inner loop keeps reading the events
        // one-by-one until there are no events left
        // to read. SDL_PollEvent(&event) just checks
        // if any new events have happend, and stores them
        // inside of the event variable.
        while (SDL_PollEvent(&event) != 0) {
            // A switch statement conditionally runs different
            // code depending on the value it is given.
            // Here we check the type of event that happened,
            // and do something different depending on what type of
            // event it was.
            switch (event.type) {
            case SDL_EVENT_JOYSTICK_ADDED:
                printf("added");
                break;
            case SDL_EVENT_JOYSTICK_REMOVED:
                printf("removed");
                break;
            case SDL_EVENT_JOYSTICK_AXIS_MOTION:
                printf("The value of axis %d was changed to %d.\n", event.jaxis.axis, event.jaxis.value);
                break;
            case SDL_EVENT_JOYSTICK_HAT_MOTION:
                printf("The hat with index %d was moved to position %d.\n", event.jhat.hat, event.jhat.value);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_DOWN:
                printf("The button with index %d was pressed.\n", event.jbutton.button);
                break;
            case SDL_EVENT_JOYSTICK_BUTTON_UP:
                printf("The button with index %d was released.\n", event.jbutton.button);
                break;
            default:
                break;
            case SDL_EVENT_QUIT:
                 quit = 1;
                 break;
#if 0
            case SDL_JOYAXISMOTION:
                printf("The value of axis %d was changed to %d.\n", event.jaxis.axis, event.jaxis.value);
                break;

            case SDL_JOYHATMOTION:
                printf("The hat with index %d was moved to position %d.\n", event.jhat.hat, event.jhat.value);
                break;

            case SDL_JOYBUTTONDOWN:
                printf("The button with index %d was pressed.\n", event.jbutton.button);
                break;

            case SDL_JOYBUTTONUP:
                printf("The button with index %d was released.\n", event.jbutton.button);
                break;

            case SDL_JOYDEVICEADDED:
                printf("A Joystick was connected and assigned index %d.\n", event.jdevice.which);
                break;

            case SDL_JOYDEVICEREMOVED:
                printf("The Joystick with index %d was removed.\n", event.jdevice.which);
                break;
#endif
            }
        }
    }

    // Free up any resources that SDL allocated.
    SDL_Quit();
    return 0;
}

#if 0
#include <iostream>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main()
{
    // TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
    // <b>lang</b> variable name to see how CLion can help you rename it.
    auto lang = "C++";
    std::cout << "Hello and welcome to " << lang << "!\n";

    for (int i = 1; i <= 5; i++)
    {
        // TIP Press <shortcut actionId="Debug"/> to start debugging your code.
        // We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
        // breakpoint for you, but you can always add more by pressing
        // <shortcut actionId="ToggleLineBreakpoint"/>.
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}

#endif

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.

