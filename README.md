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
  
## Circuit Diagram in Wokwi

![Screenshot 2025-05-08 162525](https://github.com/user-attachments/assets/b35b539e-5cfa-422f-8f27-2837b233e676)

| Component      | Pin    | Function                  |
| -------------- | ------ | ------------------------- |
| DHT22 Sensor   | Pin 2  | Reads temperature.        |
| Relay (Heater) | Pin 8  | Controls heater ON/OFF.   |
| LED            | Pin 9  | Visual status indicator.  |
| Buzzer         | Pin 10 | Audio alert for overheat. |

## How to Run

### Wokwi

- Open the Wokwi Project Link:https://wokwi.com/projects/430366188285115393
- Upload the code and run the simulation.

### VS Code
https://github.com/SACHINPV-2002/test1

## 





