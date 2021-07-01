#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "http_data_type.h"
#include "http_response.h"
#include "logger.h"

namespace tcp
{
    class ClientSocket;

    // 服务端主套接字，用于接收新的客户端连接请求
    class ServerSocket
    {
    public:
        ServerSocket(uint32_t ip = INADDR_ANY, uint16_t port = 6060);
        ServerSocket(const std::string &ip, uint16_t port = 6060);

        void Bind();
        void Listen() const;
        ClientSocket Accept() const;
        void Close() const;

        int GetSockFd() const { return serv_sock_; }
        sockaddr_in GetAddr() const { return serv_adr_; }

    private:
        struct sockaddr_in serv_adr_; // 服务器端地址
        int serv_sock_;               // 服务器端主套接字描述符
    };

    // 连接客户端的套接字，用于与客户端传输数据
    class ClientSocket
    {
        friend class ServerSocket;

    public:
        ssize_t Recv(char *const buf, size_t nbytes) const;
        ssize_t Send(const http::HttpResponse &http_response) const;
        void Close() const;

        int GetSockFd() const { return clnt_sock_; }
        sockaddr_in GetAddr() const { return clnt_adr_; }

        void Process();

    private:
        // 读取文件内容并发送出去
        size_t SendFile(const std::string &filename) const;

    private:
        int clnt_sock_;               // 用于连接客户端的套接字描述符
        struct sockaddr_in clnt_adr_; // 客户端地址
        socklen_t clnt_adr_size_;     // clnt_adr_ 的大小
    };
}
