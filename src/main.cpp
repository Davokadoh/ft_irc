#include "Server.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    int port;

    if (argc != 3)
    {
        std::cerr << "Usage: ./ft_irc PORT PASSWORD" << std::endl;
    }

    try
    {
        port = std::atoi(argv[1]);
        if (port < 1025 || port > 65536)
        {
            throw std::runtime_error("Invalid port");
        }
        Server server(argv[1], argv[2]);
        server.watch();
        server.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}
