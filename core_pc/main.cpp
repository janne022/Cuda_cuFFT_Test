#include "UsbLink.h"
#include "SignalProcessor.h"
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

    float targetStrength = processor.analyzeBatch(rawData);

    if (!targetLocked && targetStrength > TURN_ON_THRESHOLD) {
        targetLocked = true;
        antenna.sendCommand('A');
    }
    else if (targetLocked && targetStrength < TURN_OFF_THRESHOLD) {
        targetLocked = false;
        antenna.sendCommand('S');
    }
    std::cout << "----" << std::endl;
    }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}