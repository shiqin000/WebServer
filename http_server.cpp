#include "http_server.h"

void http::HttpServer::Run()
{
    Logger::Log(std::string("listening..."));
    while (true)
    {
        tcp::ClientSocket client_socket = server_socket_.Accept();
        Logger::Log(std::string("接受连接，连接方地址：") + inet_ntoa(client_socket.GetAddr().sin_addr) + ":" + std::to_string(ntohs(client_socket.GetAddr().sin_port)));
        ProcessRequest(client_socket);
        Logger::Log(std::string("IP ") + inet_ntoa(client_socket.GetAddr().sin_addr) + " 的连接处理完毕");
    }
}

void http::HttpServer::ProcessRequest(const tcp::ClientSocket &client_socket)
{
    Logger::Log("处理连接中...");
    char buf[kBufferSize];

    int read_index = 0;

    HttpRequest http_request;
    HttpResponse http_response;

    // 从客户套接字接收数据
    auto recv_len = client_socket.Recv(buf, kBufferSize - read_index);
    if (recv_len == 0)
    {
        Logger::Log("connection closed by client");
        return;
    }
    read_index += recv_len;
    Logger::Log(std::string("----接收到数据，大小为：") + std::to_string(read_index));

    // 从接收到的数据中解析出 Http 请求报文
    bool is_parse_success = HttpRequestParser::Parse(buf, http_request);

    // 根据 Http 请求报文构建 Http 响应报文
    if (is_parse_success)
    {
        Logger::Log("----请求报文解析成功");
        HttpResponseBuilder::Build(http_request, http_response);
    }
    else
    {
        Logger::Log("----请求报文解析失败");
        HttpResponseBuilder::BuildError(http_response);
    }
    Logger::Log("----响应报文构造完毕");

    // 将 Http 报文发送给客户
    client_socket.Send(http_response);
    Logger::Log("----响应报文发送完毕");
}