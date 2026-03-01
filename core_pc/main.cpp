#include "SignalProcessor.h"
#include "UsbLink.h"
#include <iostream>

int main() {
  try {

    UsbLink antenna("/dev/ttyACM1");
    SignalProcessor processor;

    std::cout << "Starting capure..." << std::endl;

    const float TURN_ON_THRESHOLD = 25000.0f;
    const float TURN_OFF_THRESHOLD = 10000.0f;

    bool targetLocked = false;

    // Capture loop
    while (true) {
      std::vector<int> rawData = antenna.readBatch(1024);

      std::cout << "Captured " << rawData.size() << " samples." << std::endl;

      PeakData targetStrength = processor.analyzeBatch(rawData);

      // Capture around 50hz that is stronger than 25k magnitude
      bool isLoudEnough = targetStrength.magnitude > TURN_ON_THRESHOLD;
      bool isCorrectHz = (targetStrength.frequency > 48.0f && targetStrength.frequency < 52.0f);

      // Turn LED on or off if there is a spike at any frequency
      if (!targetLocked && isLoudEnough && isCorrectHz) {
        targetLocked = true;
        antenna.sendCommand('A');
      } else if (targetLocked && targetStrength.magnitude < TURN_OFF_THRESHOLD) {
        targetLocked = false;
        antenna.sendCommand('S');
      }
      std::cout << "----" << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}