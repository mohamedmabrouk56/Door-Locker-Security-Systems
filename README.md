# Door-Locker-Security-Systems
![Version](https://img.shields.io/badge/Version-1-brightgreen)
![Author](https://img.shields.io/badge/Authors-Mohamed%20Mabrouk-blue)
![Date](https://img.shields.io/badge/Date-16%20MAR%202024-orange)       
Developing a system to unlock a door using a password.

## Overview

The Door Locker Security System is an AVR-based security solution utilizing an Atmega32 microcontroller. It comprises two main components: Control_ECU (Control Electronic Control Unit) and HMI_ECU (Human Machine Interface Electronic Control Unit). The system ensures secure access to premises through a password-based authentication mechanism and controls the door locking mechanism.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Hardware Setup](#hardware-setup)
- [Control_ECU](#control-ecu)
  - [Code Structure](#code-structure)
  - [API Functions](#api-functions)
  - [Main](#main)
  - [Application Source File](#application-source-file)
- [HMI_ECU](#hmi-ecu)
  - [Code Structure](#code-structure-1)
  - [API Functions](#api-functions-1)
  - [Main](#main-1)
  - [Application Source File](#application-source-file-1)
 - [Author](#author)




## Introduction

The Door Locker Security System provides a robust solution for controlling access to buildings or rooms. It ensures security through password-based authentication and enables users to manage access conveniently.

## Features

- **Password-Based Authentication:** Users can authenticate themselves using a password entered through the Human Machine Interface (HMI).
  
- **Error Handling:** The system includes error handling mechanisms to address faults and incorrect password attempts, ensuring reliability.

- **User-Friendly Interface:** The HMI_ECU features an LCD display and keypad for a user-friendly experience in setting passwords and operating the system.

- **Motor Control:** The Control_ECU manages the door locking mechanism, controlling the motor to lock or unlock the door as per authentication results.

## Hardware Setup

The hardware setup involves connecting the Atmega32 microcontroller to the Control_ECU and HMI_ECU components. Detailed connections can be found in the hardware documentation.

## Control_ECU

### Code Structure

The Control_ECU code is structured as follows:

- **main.c:** Entry point for the Control_ECU.
- **app.c:** Application source file containing functions for password management, authentication, and door control.

### API Functions

- **CONTROL_sysInit():** Initializes the system modules.
- **CONTROL_newPasswordSave():** Saves a new password received via UART.
- **CONTROL_passwordCheck():** Checks if the entered password matches the saved password.
- **CONTROL_openDoor():** Controls the opening of the door based on the current error state.
- **CONTROL_savePasswordMemory():** Saves the password to EEPROM memory.

### Main

The main source file for the Control_ECU initializes the system and controls the authentication process.

### Application Source File

The application source file contains functions for managing passwords, checking authentication, and controlling the door mechanism.

## HMI_ECU

### Code Structure

The HMI_ECU code is structured as follows:

- **main.c:** Entry point for the HMI_ECU.
- **app.c:** Application source file containing functions for setting and re-entering passwords and checking password validity.

### API Functions

- **HMI_sysInit():** Initializes the HMI system.
- **HMI_setNewPassword():** Allows the user to set a new password using the keypad.
- **HMI_ReenterPassword():** Prompts the user to re-enter the password for verification.
- **HMI_checkPassword():** Checks the password entered by the user for authentication.
- **HMI_openDoor():** Controls the opening of the door using the HMI.

### Main

The main source file for the HMI_ECU handles user interactions, including setting passwords, entering passwords for authentication, and displaying system status.

### Application Source File

The application source file implements functions for setting and re-entering passwords and checking password validity.

## Author

- [Mohamed Mabrouk](https://github.com/mohamed-mabrouk)
