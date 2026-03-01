#pragma once

#include <vector>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string>

class UsbLink{
    private:
    int fileDescriptor;
    public:
    UsbLink(const std::string& portName);
    std::vector<int> readBatch(const int& batchSize);
};