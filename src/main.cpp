#include "Server.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
  int port;
  std::string password;

  if (argc < 2) {
    std::cerr << "Usage: ./ft_irc PORT (PASSWORD)" << std::endl;
    return 0;
  }

  if (argc == 2) {
    password = "";
  } else {
    password = argv[2];
  }

  try {
    port = std::atoi(argv[1]);
    if (port < 1025 || port > 65536) {
      throw std::runtime_error("Invalid port");
    }
    Server server(argv[1], password);
    server.watch();
    server.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}
