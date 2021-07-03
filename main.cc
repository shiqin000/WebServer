#include <iostream>

#include "server.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage : " << argv[0] << " <port> " << std::endl;
        exit(0);
    }

    Logger::Log("启动服务器");
    Server server(argv[1]);
    server.Run();
    Logger::Log("关闭服务器");

    quick_exit(0);
}