#include <DHT.h>
#include <TimerOne.h>  // For timer interrupt


#define DHTPIN 2            // DHT22 Data pin
#define DHTTYPE DHT22       // DHT22 sensor type
#define RELAY_PIN 8         // Relay pin
#define LED_PIN 9           // LED pin
#define BUZZER_PIN 10       // Buzzer pin

//  Thresholds
#define TARGET_TEMP 30.0    // Target temperature in Celsius
#define HYSTERESIS 1.0      // ±1°C around target to stabilize
#define OVERHEAT_TEMP 40.0  // Overheat threshold


DHT dht(DHTPIN, DHTTYPE);
volatile bool updateFlag = false;  // Timer interrupt flag

enum State {
  IDLE,
  HEATING,
  STABILIZING,
  TARGET_REACHED,
  OVERHEAT
};

State currentState = IDLE;

//Function 
void updateState(float temp);
void logStatus(float temp);
void updateFeedback();
void timerISR();

void setup() {
  Serial.begin(9600);
  dht.begin();

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // timer interrupt (2-second)
  Timer1.initialize(2000000);  // 2,000,000 microseconds = 2 seconds
  Timer1.attachInterrupt(timerISR);

  Serial.println("System Initialized.");
}

void loop() {
  if (updateFlag) {
    float temperature = dht.readTemperature();

    if (isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      digitalWrite(RELAY_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
      noTone(BUZZER_PIN);
      currentState = IDLE;
    } else {
      updateState(temperature);
      logStatus(temperature);
    }
    updateFlag = false;  // Reset flag
  }

  updateFeedback();  //update LED/buzzer
}

// Timer ISR (runs every 2 seconds)
void timerISR() {
  updateFlag = true;
}

//State Machine 
void updateState(float temp) {
  switch (currentState) {
    case IDLE:
      if (temp < TARGET_TEMP - HYSTERESIS) {
        currentState = HEATING;
      }
      break;

    case HEATING:
      digitalWrite(RELAY_PIN, HIGH);  // Heater ON

      if (temp >= OVERHEAT_TEMP) {
        currentState = OVERHEAT;
      } else if (temp >= TARGET_TEMP - HYSTERESIS) {
        currentState = STABILIZING;
      }
      break;

    case STABILIZING:
      digitalWrite(RELAY_PIN, LOW);   // Heater OFF

      if (temp >= OVERHEAT_TEMP) {
        currentState = OVERHEAT;
      } else if (temp >= TARGET_TEMP && temp <= TARGET_TEMP + HYSTERESIS) {
        currentState = TARGET_REACHED;
      } else if (temp < TARGET_TEMP - HYSTERESIS) {
        currentState = HEATING;
      }
      break;

    case TARGET_REACHED:
      digitalWrite(RELAY_PIN, LOW);   // Heater OFF

      if (temp >= OVERHEAT_TEMP) {
        currentState = OVERHEAT;
      } else if (temp < TARGET_TEMP - HYSTERESIS) {
        currentState = HEATING;
      }
      break;

    case OVERHEAT:
      digitalWrite(RELAY_PIN, LOW);   // Heater OFF
      if (temp < OVERHEAT_TEMP - 2) {
        currentState = IDLE;
      }
      break;
  }
}

//LED/Buzzer Feedback
void updateFeedback() {
  static unsigned long lastBlinkTime = 0;
  static bool ledState = false;

  switch (currentState) {
    case IDLE:
      digitalWrite(LED_PIN, LOW);
      noTone(BUZZER_PIN);
      break;

    case HEATING:
      // Solid LED (heating in progress)
      digitalWrite(LED_PIN, HIGH);
      noTone(BUZZER_PIN);
      break;

    case STABILIZING:
      // Slow blink (500ms interval)
      if (millis() - lastBlinkTime >= 500) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        lastBlinkTime = millis();
      }
      noTone(BUZZER_PIN);
      break;

    case TARGET_REACHED:
      // LED off (target reached)
      digitalWrite(LED_PIN, LOW);
      noTone(BUZZER_PIN);
      break;

    case OVERHEAT:
      // Fast blink (200ms) + buzzer beep
      if (millis() - lastBlinkTime >= 200) {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
        tone(BUZZER_PIN, 1000, 100);  // 1kHz beep for 100ms
        lastBlinkTime = millis();
      }
      break;
  }
}

//Logging
void logStatus(float temp) {
  String stateStr;
  switch (currentState) {
    case IDLE: stateStr = "Idle"; break;
    case HEATING: stateStr = "Heating"; break;
    case STABILIZING: stateStr = "Stabilizing"; break;
    case TARGET_REACHED: stateStr = "Target Reached"; break;
    case OVERHEAT: stateStr = "Overheat"; break;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C | State: ");
  Serial.print(stateStr);
  Serial.print(" | Heater: ");
  Serial.println(digitalRead(RELAY_PIN) ? "ON" : "OFF");
}