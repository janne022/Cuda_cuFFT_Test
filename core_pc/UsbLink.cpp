#include "UsbLink.h"
#include <unistd.h>

UsbLink::UsbLink(const std::string &portName) {

    // Open USB port to get raw data
  fileDescriptor = open(portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);

  // Holds settings of port
  struct termios tty;
  if (tcgetattr(fileDescriptor, &tty) != 0) {
  }

  // Set speed to match ESP32
  cfsetospeed(&tty, B115200);
  cfsetispeed(&tty, B115200);

  // Set flags: no parity, 1 stop bit, clear size mask, 8 data bits, raw mode.
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

  // Apply tty to fileDescriptor. Delete any stale data via tcflush.
  tcsetattr(fileDescriptor, TCSANOW, &tty);
  tcflush(fileDescriptor, TCIFLUSH);
};

UsbLink::~UsbLink() {
    // If the fileDescriptor is valid. Free it by closing the fileDescriptor.
    if (fileDescriptor > 0) {
        close(fileDescriptor);
    }
}

std::vector<int> UsbLink::readBatch(const int &batchSize) {
  std::vector<int> batch;
  std::string currentLine = "";
  char ch;

  // Loop until we reach batchSize
  while (batch.size() < static_cast<size_t>(batchSize)) {
    // Read 1 byte at a time from the USB buffer
    ssize_t n = read(fileDescriptor, &ch, 1);

    if (n > 0) {
      if (ch == '\n' || ch == '\r') {
        if (!currentLine.empty()) {
          try {
            // Convert string number to int and push it into vector.
            batch.push_back(std::stoi(currentLine));
          } catch (...) {}
          currentLine = "";
        } 
      }
      // Check if ch is number and in that case add it to currentLine
      else if (std::isdigit(static_cast<unsigned char>(ch))) {
          currentLine += ch;
        }
    }
    else if (n < 0 && errno != EAGAIN) {
        break;
      }
  };
  return batch;
};

// Take char and write to our fileDescriptor
void UsbLink::sendCommand(char cmd){
    ssize_t bytesWritten = write(fileDescriptor, &cmd, 1);
}
