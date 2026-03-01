#include "UsbLink.h"

UsbLink::UsbLink(const std::string &portName) {
  fileDescriptor = open(portName.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
  struct termios tty;
  if (tcgetattr(fileDescriptor, &tty) != 0) {
  }

  // Set speed
  cfsetospeed(&tty, B115200);
  cfsetispeed(&tty, B115200);

  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

  tcsetattr(fileDescriptor, TCSANOW, &tty);
  tcflush(fileDescriptor, TCIFLUSH);
};

std::vector<int> UsbLink::readBatch(const int &batchSize) {
  std::vector<int> batch;
  std::string currentLine = "";
  char ch;

  while (batch.size() < static_cast<size_t>(batchSize)) {
    ssize_t n = read(fileDescriptor, &ch, 1);

    if (n > 0) {
      if (ch == '\n' || ch == '\r') {
        if (!currentLine.empty()) {
          try {
            batch.push_back(std::stoi(currentLine));
          } catch (...) {}
          currentLine = "";
        } 
      }
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
