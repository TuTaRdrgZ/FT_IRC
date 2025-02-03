#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <cstring>
#include <iostream>

#define PORT 8080

int main() {
  int sock = 0;
  struct sockaddr_in serv_addr;

  // Create socket
  // @params
  // AF_INET: indicates the socket will use the IPv4 address family
  // SOCK_STREAM: indicates the socket will use the TCP protocol
  // (stream-oriented protocol) 0: indicates the protocol (if you set it to 0,
  // the OS will choose the appropriate protocol)
  // @return integer value that will store the socket file descriptor
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "Socket creation error" << std::endl;
    return -1;
  }

  // We then define the server address using the following set of statements
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary
  if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
    std::cerr << "Invalid address/ Address not supported" << std::endl;
    return -1;
  }

  // Connect to server
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    std::cerr << "Connection Failed" << std::endl;
    return -1;
  }
  std::string message = "";

  // Send data
  while (message != "exit") {
    std::cin >> message;
    send(sock, message.c_str(), message.size(), 0);
  }

  // Close socket
  close(sock);
  return 0;
}
