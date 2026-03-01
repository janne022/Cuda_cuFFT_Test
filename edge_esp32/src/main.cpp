#include <Arduino.h>

const int ANTENNA_PIN = A3;
const int WARNING_LED = D2;

void setup(){
    Serial.begin(115200);

    pinMode(ANTENNA_PIN, INPUT);

    pinMode(WARNING_LED, OUTPUT);
    digitalWrite(WARNING_LED, LOW);
}

void loop(){
    int rawNoise = analogRead(ANTENNA_PIN);

    Serial.println(rawNoise);

    if (Serial.available() > 0) {
        char incomingCommand = Serial.read();

        if (incomingCommand == 'A') {
            digitalWrite(WARNING_LED, HIGH);
        }
        else if (incomingCommand == 'S') {
            digitalWrite(WARNING_LED, LOW);
        }
    }

    delay(2);
}