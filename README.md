# Temperature State Tracker

This project simulates a temperature-based control system using Wokwi and Visual Studio Code with PlatformIO.

## Components:
- **DHT22 Temperature Sensor:** Reads temperature.
- **Relay Module:** Simulates heater control.
- **LED:** Visual indicator.
- **Buzzer:** Beeps in overheat condition.

## Core Features:
- Reads temperature every 2 seconds.
- 5 states: Idle, Heating, Stabilizing, Target Reached, Overheat.
- Controls simulated outputs:
    - Heater ON/OFF
    - LED (solid/blink)
    - Buzzer (overheat alert)
- Logs data to Serial Monitor.

## How to Run:
1. Open in Wokwi simulator.
2. Compile and upload using PlatformIO in VS Code.

   
