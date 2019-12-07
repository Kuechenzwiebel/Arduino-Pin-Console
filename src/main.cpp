#include <Arduino.h>
#include <ArduinoSTL.h>

#define MIN_PIN 2
#define MAX_PIN 13

float map(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int pinStates[MAX_PIN - MIN_PIN + 1] = {
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1
};

bool usePresetPinStates = true;
std::string in;

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);

  if(usePresetPinStates == false) {
    for(int pin = MIN_PIN; pin < MAX_PIN + 1; pin++) {
      std::cout << "Pin: " << pin << " ";
      std::cin >> in;

      if(in == "in" || in == "IN") {
        pinStates[pin - MIN_PIN] = INPUT;
      }
      else if(in == "out" || in == "OUT") {
        pinStates[pin - MIN_PIN] = OUTPUT;
      }
      else {
        Serial.print("Unknown Input");
      }
      Serial.println();
    }
  }

  for(int pin = MIN_PIN; pin < MAX_PIN + 1; pin++) {
    pinMode(pin, pinStates[pin - MIN_PIN]);
  }
  Serial.println("Configuration done!");
}

void loop() {
  std::cin >> in;
  if(in == "high" || in == "HIGH") {
    Serial.print("high\t");
    Serial.print("pin:\t");

    int pin;
    std::cin >> pin;

    if(pin >= MIN_PIN && pin <= MAX_PIN) {
      if(pinStates[pin - MIN_PIN] != OUTPUT) {
        std::cout << "Pin " << pin << " is not an output" << std::endl;
      }
      else {
        digitalWrite(pin, HIGH);
        Serial.println();
      }
    }
    else {
      std::cout << "Illegal pin number: " << pin << std::endl;
    }
  }

  else if(in == "low" || in == "LOW") {
    Serial.print("low\t");
    Serial.print("pin:\t");

    int pin;
    std::cin >> pin;

    if(pin >= MIN_PIN && pin <= MAX_PIN) {
      if(pinStates[pin - MIN_PIN] != OUTPUT) {
        std::cout << "Pin " << pin << " is not an output" << std::endl;
      }
      else {
        digitalWrite(pin, LOW);
        Serial.println();
      }
    }
    else {
      std::cout << "Illegal pin number: " << pin << std::endl;
    }
  }


  else if(in == "read" || in == "READ") {
    Serial.print("read\t");
    Serial.print("pin:\t");

    int pin;
    std::cin >> pin;

    if(pin >= MIN_PIN && pin <= MAX_PIN) {
      if(pinStates[pin - MIN_PIN] != INPUT) {
        std::cout << "Pin " << pin << " is not an input" << std::endl;
      }
      else {
        Serial.println(digitalRead(pin));
      }
    }
    else {
      std::cout << "Illegal pin number: " << pin << std::endl;
    }
  }


    else if(in == "analogread" || in == "ANALOGREAD") {
      Serial.print("analog read\t");
      Serial.print("pin:\t");

      int pin;
      std::cin >> pin;
      Serial.println();

      int read = analogRead(pin);
      Serial.println(read);
      std::cout << map(float(read), 0.0f, 1023.0f, 0.0f, 5.0f) << "V" << std::endl;
    }

  else if(in == "pulse" || in == "PULSE") {
    Serial.print("pulse\t");
    Serial.print("pin:\t");

    int pin;
    std::cin >> pin;

    Serial.print("pulse width:\t");

    int width;
    std::cin >> width;

    if(pin >= MIN_PIN && pin <= MAX_PIN) {
      if(pinStates[pin - MIN_PIN] != OUTPUT) {
        std::cout << "Pin " << pin << " is not an output" << std::endl;
      }
      else {
        digitalWrite(pin, HIGH);
        delay(width);
        digitalWrite(pin, LOW);
        Serial.println();
      }
    }
    else {
      std::cout << "Illegal pin number: " << pin << std::endl;
    }
  }

  else if(in == "rpulse" || in == "RPULSE") {
    Serial.print("repeated pulse\t");
    Serial.print("pin:\t");

    int pin;
    std::cin >> pin;

    Serial.print("pulse width:\t");

    int width;
    std::cin >> width;

    Serial.print("number of pulses:\t");

    int pulses;
    std::cin >> pulses;

    if(pin >= MIN_PIN && pin <= MAX_PIN) {
      if(pinStates[pin - MIN_PIN] != OUTPUT) {
        std::cout << "Pin " << pin << " is not an output" << std::endl;
      }
      else {
        for(int i = 0; i < pulses; i++) {
          digitalWrite(pin, HIGH);
          delay(width);
          digitalWrite(pin, LOW);
          delay(width);
        }
        Serial.println();
      }
    }
    else {
      std::cout << "Illegal pin number: " << pin << std::endl;
    }
  }

  else if(in == "pinmodes" || in == "PINMODES") {
    Serial.println("Pin modes:");
    for(int i = MIN_PIN; i < MAX_PIN + 1; i++) {
      std::cout << pinStates[i - MIN_PIN];
      if(i != MAX_PIN) {
        std::cout << ",";
      }
      std::cout << std::endl;
    }
  }

  else if(in == "pinstates" || in == "PINSTATES") {
    Serial.println("Pin states:");
    std::cout << "Pin:\t";
    for(int i = MIN_PIN; i < MAX_PIN + 1; i++) {
      Serial.print("|");
      if(i < 10) {
        Serial.print("0");
      }
      Serial.print(i);
    }
    std::cout << "|" << std::endl;
    std::cout << "State:\t";

    for(int i = MIN_PIN; i < MAX_PIN + 1; i++) {
      if(pinStates[i - MIN_PIN] == INPUT) {
        std::cout << "|i" << digitalRead(i);
      }
      else if(pinStates[i - MIN_PIN] == OUTPUT) {
        std::cout << "|o" << digitalRead(i);
      }
    }
    std::cout << "|" << std::endl;
  }


  else {
    std::cout << "Unknown command: " << in << std::endl;
  }
}
