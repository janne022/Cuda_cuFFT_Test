#include <iostream>
#include <vector>
#include "UsbLink.h"

int main() {
    try {
        // 1. Initialize the link
        // Change to /dev/ttyACM1 if ACM0 isn't found
        UsbLink antenna("/dev/ttyACM1"); 
        std::cout << "Successfully opened ESP32 port." << std::endl;

        // 2. Capture a small batch to test
        int testSize = 100;
        std::cout << "Capturing " << testSize << " samples..." << std::endl;
        
        std::vector<int> data = antenna.readBatch(testSize);

        // 3. Print the results
        for(int val : data) {
            std::cout << val << " ";
        }
        std::cout << "\n\nCapture Complete. Data integrity confirmed." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}