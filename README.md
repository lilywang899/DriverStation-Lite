# LibDS

[![Build Status](https://travis-ci.org/FRC-Utilities/LibDS.svg?branch=master)](https://travis-ci.org/FRC-Utilities/LibDS)

The DriverStation library allows you to connect and manage a robot easily by providing an abstraction layer between an application and the network comununications between the robot and the host computer.

The library is written in C, allowing it to be used in many platforms and/or programming languages (using wrappers).

## Credit
This code was originally inspired by [FRC-Utilities/LibDS](https://github.com/FRC-Utilities/LibDS/tree/master) created by [Alex Spataru]. 

### Features

LibDS implements the following features:

- Modular design
- Dynamic protocol loading
- Integrated event system
- Joystick handling functions
- Safety features
- Abstract-protocol object
- Cross-platform socket handling 

Significant modifications and improvements include:

- Migrated legacy SDL modules and developed a joystick testing tool to troubleshoot connectivity and proper functionality 
- Implemented dynamic configuration for driver station and robot simulator using YAML and XML files
- Developed a robot simulator using python to test driver station functionalities for multiple protocols 
- Implemented multi-threaded async socket communication between driver station and robot simulator 
- Used data driven robot behavior testing by storing test data in JSON file and integrating comprehensive log module

Work in progress:

- Adding FRC 2025 protocol to driver station to ensure compatibility with this year's FRC robot
- Connecting driver station with a [robot agent])(https://github.com/lilywang899/Robot-Agent) to reduce load of robot and replace RoboRIO with Raspberry Pi 
  
### Project Architecture

#### 'Private' vs. 'Public' members

- All the functions that a client application would be interested in are located in [`DS_Client.h`](https://github.com/FRC-Utilities/LibDS-C/blob/master/include/DS_Client.h). 

- Functions that are used by the protocols to update the state of the LibDS are made available in [`DS_Config.h`](https://github.com/FRC-Utilities/LibDS-C/blob/master/include/DS_Config.h). Calling any of the 'setter' functions in [`DS_Config`](https://github.com/FRC-Utilities/LibDS-C/blob/master/include/DS_Config.h) will trigger an event (which can later be used by the client application).

#### Protocols

Protocols are encapsulated structures. When a protocol is initialized, it defines its properties and its respective data functions. The different functions of the LibDS will then operate with the data and properties defined by the current protocol.

As with the original LibDS, protocols have access to the `DS_Config` to update the state of the LibDS.

The base protocol is implemented in the [`DS_Protocol`](https://github.com/FRC-Utilities/LibDS-C/blob/master/include/DS_Protocol.h#L33) structure.

##### Sockets

Instead of manually initializing a socket for each target, data direction and protocol type (UDP and TCP). The LibDS will use the [`DS_Socket`](https://github.com/FRC-Utilities/LibDS-C/blob/master/include/DS_Socket.h#L56) object to define ports, protocol type and remote targets. 

All the logic code is in [`socket.c`](https://github.com/FRC-Utilities/LibDS-C/blob/master/src/socket.c), which will be in charge of managing the system sockets with the information given by a [`DS_Socket`](https://github.com/FRC-Utilities/LibDS-C/blob/master/include/DS_Socket.h#L56) object.

### Compilation instructions

To compile the project, navigate to the project root and run the following commands

* qmake
* make

If your project runs into runtime errors try running `make staticlib` instead of `make`

To install compiled library files, and headers to the correct locations in /usr/local, use this command
* sudo make install

# ConsoleDS

A simple DS implementatation for command line interfaces with ncurses/pdcurses. Joystick support implemented with SDL.

### Dependencies

If you are using Linux, you will need to install the following packages:

- `sudo apt-get install libsdl1.2-dev`
- `sudo apt-get install ncurses-dev`

If you are using Mac OSX, use [HomeBrew](http://brew.sh) to install ncurses:

- `brew install ncurses`

I have already included the static SDL library for OSX users.
This project already provides the libraries for Microsoft Windows.

### License

This project is released under the MIT license.
