#include "UsbLink.h"
#include "SignalProcessor.h"
#include <iostream>

int main() {
    try {
    UsbLink antenna("/dev/ttyACM1");
    SignalProcessor processor;

    std::cout << "Starting capure..." << std::endl;

    // Capture loop
    while (true) {
        std::vector<int> rawData = antenna.readBatch(1024);

    std::cout << "Captured " << rawData.size() << " samples." << std::endl;

    processor.analyzeBatch(rawData);
    std::cout << "----" << std::endl;
    }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}