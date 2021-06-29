#pragma once

#include <string>
#include <cstring>
#include <exception>

#include "logger.h"
#include "http_request.h"

namespace http
{
    // HTTP 请求报文解析器
    class HttpRequestParser
    {
    public:
        static bool Parse(char *request_message, HttpRequest &http_request);

    private:
        static bool ParseRequestLine(char *request_line, HttpRequest &http_request);
        static bool ParseHeadLines(char *head_lines, HttpRequest &http_request);
        static bool ParseBody(char *body_lines, HttpRequest &http_request);

        static bool ParseHeadLine(char *head_line, HttpRequest &http_request);
    };
}
