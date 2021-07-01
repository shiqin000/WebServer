#include "http_server.h"
#include "thread_pool.h"

void http::HttpServer::Run()
{
    Logger::Log(std::string("listening..."));
    std::shared_ptr<ThreadPool> thread_pool = ThreadPool::GetInstance();
    while (true)
    {
        tcp::ClientSocket client_socket = server_socket_.Accept();
        Logger::Log(std::string("接受连接，连接方地址：") + inet_ntoa(client_socket.GetAddr().sin_addr) + ":" + std::to_string(ntohs(client_socket.GetAddr().sin_port)));
        thread_pool->Append(client_socket);
        Logger::Log(std::string("IP ") + inet_ntoa(client_socket.GetAddr().sin_addr) + " 的连接处理完毕");
    }
}