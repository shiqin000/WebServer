#include "tcp_socket.h"

tcp::ServerSocket::ServerSocket(uint32_t ip, uint16_t port)
{
    serv_sock_ = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr_, 0, sizeof(serv_adr_));
    serv_adr_.sin_family = AF_INET;
    serv_adr_.sin_addr.s_addr = htonl(ip);
    serv_adr_.sin_port = htons(port);
}

tcp::ServerSocket::ServerSocket(const std::string &ip, uint16_t port)
{
    serv_sock_ = socket(PF_INET, SOCK_STREAM, 0);

    memset(&serv_adr_, 0, sizeof(serv_adr_));
    serv_adr_.sin_family = AF_INET;
    if (ip.empty())
    {
        serv_adr_.sin_addr.s_addr = htonl(INADDR_ANY);
    }
    else
    {
        if (inet_aton(ip.c_str(), &serv_adr_.sin_addr) == 0)
            Logger::Error("inet_aton() error");
    }
    serv_adr_.sin_port = htons(port);
}

void tcp::ServerSocket::Bind()
{
    if (::bind(serv_sock_, (struct sockaddr *)&serv_adr_, sizeof(serv_adr_)) == -1)
    {
        Logger::Error("系统调用失败：bind() error");
        exit(0);
    }
}

void tcp::ServerSocket::Listen() const
{
    if (::listen(serv_sock_, 5) == -1)
    {
        Logger::Error("系统调用失败：listen() error");
        exit(0);
    }
}

tcp::ClientSocket tcp::ServerSocket::Accept() const
{
    ClientSocket client_socket;
    client_socket.clnt_sock_ = ::accept(serv_sock_,
                                        (struct sockaddr *)&client_socket.clnt_adr_,
                                        &client_socket.clnt_adr_size_);
    if (client_socket.clnt_sock_ == -1)
        Logger::Log("系统调用失败：accept() error.");

    return client_socket;
}

void tcp::ServerSocket::Close() const
{
    ::close(serv_sock_);
}

void tcp::ClientSocket::Close() const
{
    ::close(clnt_sock_);
}

ssize_t tcp::ClientSocket::Recv(char *const buf, size_t nbytes) const
{
    auto recv_len = ::recv(clnt_sock_, buf, nbytes, 0);
    if (recv_len == -1)
    {
        Logger::Error("系统调用失败：recv() error");
        exit(0);
    }
    return recv_len;
}

ssize_t tcp::ClientSocket::Send(const http::HttpResponse &http_response) const
{
    size_t send_len = 0;

    // 发送状态行及首部信息
    send_len += ::send(clnt_sock_, http_response.GetResponseStr(), strlen(http_response.GetResponseStr()), 0);

    // 发送消息主体
    send_len += SendFile(http_response.GetFilename());

    return send_len;
}

size_t tcp::ClientSocket::SendFile(const std::string &filename) const
{
    size_t send_len = 0;

    FILE *clnt_write = fdopen(clnt_sock_, "w");
    FILE *send_file = fopen(filename.c_str(), "r");
    if (send_file == NULL)
    {
        return 0;
    }

    char buf[http::kBufferSize];

    while (fgets(buf, http::kBufferSize, send_file) != NULL)
    {
        fputs(buf, clnt_write);
        fflush(clnt_write);
    }
    fflush(clnt_write);
    fclose(clnt_write);

    return send_len;
}
