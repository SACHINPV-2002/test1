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

## How It Works

The system tracks temperature and transitions between 5 states based on preset thresholds.

| **State**            | **Condition to Enter**                                      | **Outputs**                                                                      |
|----------------------|-------------------------------------------------------------|----------------------------------------------------------------------------------|
| 💤 **Idle**          | Initial state or when temperature drops below 38°C (after overheat) or sensor error | - Heater: OFF<br>- LED: OFF<br>- Buzzer: OFF                                     |
| 🔥 **Heating**       | Temperature < 29°C (Target - 1°C Hysteresis)                | - Heater: ON<br>- LED: Solid ON<br>- Buzzer: OFF                                 |
| ⚖️ **Stabilizing**   | Temperature ≥ 29°C and < 30°C                               | - Heater: OFF<br>- LED: Slow Blink (500ms)<br>- Buzzer: OFF                      |
| ✅ **Target Reached**| Temperature between 30°C and 31°C (Target ± 1°C)            | - Heater: OFF<br>- LED: OFF                                                      |
| 🚨 **Overheat**      | Temperature ≥ 40°C                                         | - Heater: OFF<br>- LED: Fast Blink (200ms)<br>- Buzzer: Beeps (1kHz tone, 100ms) |

**Thresholds:**
- 🎯 **Target Temp:** 30.0°C
- 🔄 **Hysteresis Band:** ±1.0°C
- 🚨 **Overheat Temp:** 40.0°C


- The system **reads temperature every 2 seconds**.
- It **logs the temperature, state, and heater status** to the Serial Monitor.
- Transitions happen **automatically** based on the temperature reading.


If the sensor fails to read, the system resets to **Idle** and turns everything off.







