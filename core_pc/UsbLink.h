#pragma once

#include <fcntl.h>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

class UsbLink {
private:
  int fileDescriptor;

public:
  UsbLink(const std::string &portName);
  std::vector<int> readBatch(const int &batchSize);

  void sendCommand(char cmd);
};