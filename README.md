# Temperature Based State Tracker

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

## OUTPUTS
CASE 1: HEATING

https://github.com/user-attachments/assets/35f23b9d-5c7c-4e6f-807e-68bee2f478ae

- The LED is ON which indicates that the Heater is currently turned on.

CASE 2: STABILIZING

https://github.com/user-attachments/assets/26c64ba9-16de-4513-bbfb-e4402e8d64cb

- Current temperature is 29.40 degree Celsius; Therefore, the system starts stabilizing (29°C ≤ Temp < 30°C). 
- The LED is blinking slowly to indicate the state

CASE 3: TARGET REACHED

https://github.com/user-attachments/assets/2bdef6af-5cc6-46fc-8be4-cc54b1d49403

- Current temperature is 30.40 degree Celsius; Therefore, the target temperature has been reached.
- The LED is off indicating that the heater is turned off.

CASE 4: OVERHEATING

https://github.com/user-attachments/assets/0969fe70-73b1-4785-9898-7fa16861e271

- Temperature recorded is 46.50 degree Celsius; Therefore, the system is in overheating state.
- This is indicated by the rapidly blinking LED and the Buzzer Beep.

CASE 5: IDLE

https://github.com/user-attachments/assets/4e7e5ec2-49b3-4d37-a1ca-034046b8db0b

- Temperature recorded is 36.30 degree Celsius; Therefore, the system is in idle state.











