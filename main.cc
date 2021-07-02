#include <iostream>

#include "http_server.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage : " << argv[0] << " <port> " << std::endl;
        exit(0);
    }

    Logger::Log("启动服务器");
    http::HttpServer http_server(argv[1]);
    http_server.Run();
    Logger::Log("关闭服务器");
}