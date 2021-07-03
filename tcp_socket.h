#pragma once

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <string>
#include <iostream>
#include <fstream>

#include "logger.h"
#include "http_data_type.h"
#include "http_response.h"

namespace tcp
{
    class ClientSocket;

    // 服务端主套接字，用于接收新的客户端连接请求
    class ServerSocket
    {
    public:
        ServerSocket();
        ServerSocket(uint16_t port);
        ServerSocket(uint32_t ip, uint16_t port);
        ServerSocket(const std::string &ip, uint16_t port);

        void Bind() const;
        void Listen() const;
        ClientSocket Accept() const;
        void Close() const;

        inline int GetSockFd() const { return serv_sock_; }
        inline sockaddr_in GetAddr() const { return serv_adr_; }

    private:
        static constexpr uint32_t kDefaultIp = INADDR_ANY;
        static constexpr uint16_t kDefaultPort = 5000;

        void ServAddrInit(uint32_t ip, uint16_t port);

    private:
        struct sockaddr_in serv_adr_; // 服务器端地址
        int serv_sock_;               // 服务器端主套接字描述符
    };

    // 连接客户端的套接字，用于与客户端传输数据
    class ClientSocket
    {
        friend class ServerSocket;

    public:
        ClientSocket() : clnt_sock_(0), clnt_adr_size_(sizeof(sockaddr_in)) {}
        ClientSocket(int clnt_sock) : clnt_sock_(clnt_sock), clnt_adr_size_(sizeof(sockaddr_in)) {}

        ssize_t Recv(char *const buf, size_t nbytes) const;
        ssize_t Send(const http::HttpResponse &http_response) const;
        void Close() const;

        inline int GetSockFd() const { return clnt_sock_; }
        inline sockaddr_in GetAddr() const { return clnt_adr_; }

        void Process() const;

    private:
        // 读取文件内容并发送出去
        size_t SendFile(const std::string &filename) const;

    private:
        int clnt_sock_;               // 用于连接客户端的套接字描述符
        struct sockaddr_in clnt_adr_; // 客户端地址
        socklen_t clnt_adr_size_;     // clnt_adr_ 的大小
    };
} // namespace tcp
