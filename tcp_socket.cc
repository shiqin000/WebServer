#include "tcp_socket.h"
#include "http_request.h"
#include "http_request_parser.h"
#include "http_response_builder.h"

tcp::ServerSocket::ServerSocket()
{
    serv_sock_ = socket(PF_INET, SOCK_STREAM, 0);
    ServAddrInit(kDefaultIp, kDefaultPort);
}

tcp::ServerSocket::ServerSocket(uint16_t port)
{
    serv_sock_ = socket(PF_INET, SOCK_STREAM, 0);
    ServAddrInit(kDefaultIp, port);
}

tcp::ServerSocket::ServerSocket(uint32_t ip, uint16_t port)
{
    serv_sock_ = socket(PF_INET, SOCK_STREAM, 0);
    ServAddrInit(ip, port);
}

tcp::ServerSocket::ServerSocket(const std::string &ip, uint16_t port)
{
    serv_sock_ = socket(PF_INET, SOCK_STREAM, 0);

    if (ip.empty())
    {
        ServAddrInit(kDefaultIp, port);
    }
    else
    {
        ServAddrInit(inet_addr(ip.c_str()), port);
    }
}

void tcp::ServerSocket::ServAddrInit(uint32_t ip, uint16_t port)
{
    memset(&serv_adr_, 0, sizeof(serv_adr_));
    serv_adr_.sin_family = AF_INET;
    serv_adr_.sin_addr.s_addr = htonl(ip);
    serv_adr_.sin_port = htons(port);
}

void tcp::ServerSocket::Bind() const
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
    return ::recv(clnt_sock_, buf, nbytes, 0);
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

void tcp::ClientSocket::Process() const
{
    Logger::Log("处理连接中...");
    char buf[http::kBufferSize];

    int read_index = 0;

    while (read_index < http::kBufferSize)
    {
        ssize_t recv_len = Recv(buf + read_index, http::kBufferSize - read_index - 1);
        if (recv_len < 0)
        {
            if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
            {
                break;
            }
            close(clnt_sock_);
            break;
        }
        else if (recv_len == 0) // 读取到 EOF，表示对方已关闭连接
        {
            close(clnt_sock_);
            return;
        }
        else
        {
            read_index += recv_len;
        }
    }

    Logger::Log(std::string("----接收到数据，大小为：") + std::to_string(read_index));

    // 从接收到的数据中解析出 Http 请求报文
    http::HttpRequest http_request;
    bool is_parse_success = http::HttpRequestParser::Parse(buf, http_request);

    // 根据 Http 请求报文构建 Http 响应报文
    http::HttpResponse http_response;
    if (is_parse_success)
    {
        Logger::Log("----请求报文解析成功");
        http::HttpResponseBuilder::Build(http_request, http_response);
    }
    else
    {
        Logger::Log("----请求报文解析失败");
        http::HttpResponseBuilder::BuildError(http_response);
    }
    Logger::Log("----响应报文构造完毕");

    // 将 Http 报文发送给客户
    Send(http_response);
    Logger::Log("----响应报文发送完毕");

    Close();
}