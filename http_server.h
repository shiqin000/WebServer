#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "logger.h"
#include "http_data_type.h"
#include "tcp_socket.h"
#include "http_request.h"
#include "http_request_parser.h"
#include "http_response.h"
#include "http_response_builder.h"

namespace http
{
    class HttpServer
    {
    public:
        HttpServer()
        {
            server_socket_.Bind();
            server_socket_.Listen();
        }

        explicit HttpServer(const char *const port) : server_socket_(INADDR_ANY, std::stoi(port))
        {
            server_socket_.Bind();
            server_socket_.Listen();
        }

        void Run();

    private:
        tcp::ServerSocket server_socket_;
    };
}
