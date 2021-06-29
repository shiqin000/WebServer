#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "http_data_type.h"
// #include "http_request_parser.h"
// #include "http_response_builder.h"

#define CR '\r'
#define LF '\n'
#define CRLF "\r\n"

namespace http
{
    // HTTP 请求报文
    class HttpRequest
    {
        friend class HttpRequestParser;
        friend class HttpResponseBuilder;

    public:
        HttpRequest() : request_method_(HttpRequestMethod::METHOD_NOT_SUPPORT),
                        http_version_(HttpVersion::VERSION_NOT_SUPPORT) {}

    private:
        HttpRequestMethod request_method_;
        std::string uri_;
        HttpVersion http_version_;
        std::unordered_map<std::string, std::string> head_group_;
        std::string body_;
    };
}
