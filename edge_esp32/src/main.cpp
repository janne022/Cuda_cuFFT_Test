#include <Arduino.h>

const int ANTENNA_PIN = A3;
const int WARNING_LED = D2;

void setup(){
    // Bit speed
    Serial.begin(115200);

    // Listen to voltages
    pinMode(ANTENNA_PIN, INPUT);

    // Send voltages
    pinMode(WARNING_LED, OUTPUT);
    digitalWrite(WARNING_LED, LOW);
}

void loop(){
    // Read electromagnetic voltages on wire, converts into int.
    int rawNoise = analogRead(ANTENNA_PIN);

    // Print new line with voltage and print to USB.
    Serial.println(rawNoise);

    // If kernel has written bytes we read it. If char is A we turn on light, if it is S we turn off light.
    if (Serial.available() > 0) {
        char incomingCommand = Serial.read();

        if (incomingCommand == 'A') {
            digitalWrite(WARNING_LED, HIGH);
        }
        else if (incomingCommand == 'S') {
            digitalWrite(WARNING_LED, LOW);
        }
    }

    // Determines sample rate.
    delay(2);
}