# RoboticsLEDs – LED Animations for Cubo Submarine

This project provides custom LED animations for **Cubo**, the underwater autonomous vehicle developed by Robotics@Maryland. The system uses an Arduino Nano and the FastLED library to control addressable LEDs for signaling different robot states.

## Summary

The Arduino Nano controls LED animations for the Cubo submarine and receives commands from the Jetson onboard computer using two digital input pins. Depending on the pin combination, the Arduino plays different animations corresponding to specific robot states: initialization, diving, or running.

This system provides intuitive visual feedback for developers and observers during operation and debugging, especially during pool testing and live runs.

## Features

- Custom animations for:
  - Initialization sequence
  - Dive mode
  - Running state
- Compact implementation using Arduino Nano
- Communication interface using two GPIO lines from Jetson
- Designed for clarity and visibility in low-light or underwater conditions
- Powered by the FastLED library

## Hardware

- Arduino Nano
- WS2812 or compatible addressable LEDs
- Jetson (or any companion computer)
- 2 digital GPIO lines (Jetson → Arduino)
- 5V power supply (regulated)

## Software

- [FastLED](https://github.com/FastLED/FastLED)
- Custom Arduino sketch with state-based animation logic
- Simple protocol using digital pin combinations (2 bits = 4 possible animations)

## How It Works

1. The Jetson sets two digital output pins to represent the current system state.
2. The Arduino Nano reads these pins and maps them to an animation ID.
3. The corresponding LED pattern is played until a new command is received.

| Pin A | Pin B | Mode           |
|-------|--------|----------------|
|   0   |   0    | Idle           |
|   0   |   1    | Initialization |
|   1   |   0    | Diving         |
|   1   |   1    | Running        |

## Project Context

This code was developed as part of the Cubo submarine project by **Robotics@Maryland**, a student robotics team at the University of Maryland. The LED system enhances usability, diagnostics, and visual feedback during development and autonomous missions.

## Author

**Brian Zagalsky**  
