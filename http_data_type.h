#pragma once

#include <unordered_map>

namespace http
{
    constexpr int kBufferSize = 2048;

    enum class HttpRequestMethod
    {
        GET,
        POST,
        PUT,
        HEAD,
        DELETE,
        METHOD_NOT_SUPPORT
    };

    enum class HttpStatusCode
    {
        k200,
        k403,
        k404
    };

    enum class HttpVersion
    {
        HTTP_1_0,
        HTTP_1_1,
        VERSION_NOT_SUPPORT
    };

    enum class HttpHead
    {
        kHost,
        kDate,
        kUserAgent,
        kConnection,
        kAcceptCharset,
        kAcceptEncoding,
        kAcceptLanguage,
        kCacheControl,
        kHeadNotSupport
    };

    namespace mapper
    {
        const std::unordered_map<std::string, http::HttpRequestMethod> request_method = {
            {"GET", http::HttpRequestMethod::GET},
            {"POST", http::HttpRequestMethod::POST},
            {"PUT", http::HttpRequestMethod::PUT},
            {"HEAD", http::HttpRequestMethod::HEAD},
            {"DELETE", http::HttpRequestMethod::DELETE}};

        const std::unordered_map<std::string, http::HttpVersion> http_version = {
            {"HTTP/1.0", http::HttpVersion::HTTP_1_0},
            {"HTTP/1.1", http::HttpVersion::HTTP_1_1}};

        const std::unordered_map<std::string, http::HttpHead> head = {};

        const std::unordered_map<std::string, std::string> content_type = {
            {".html", "text/html"},
            {".xml", "text/xml"},
            {".xhtml", "application/xhtml+xml"},
            {".txt", "text/plain"},
            {".rtf", "application/rtf"},
            {".pdf", "application/pdf"},
            {".word", "application/msword"},
            {".png", "image/png"},
            {".gif", "image/gif"},
            {".jpg", "image/jpeg"},
            {".jpeg", "image/jpeg"},
            {".au", "audio/basic"},
            {".mpeg", "video/mpeg"},
            {".mpg", "video/mpeg"},
            {".avi", "video/x-msvideo"},
            {".gz", "application/x-gzip"},
            {".tar", "application/x-tar"},
            {".css", "text/css"},
            {"", "text/plain"},
            {"default", "text/plain"}};

        const std::unordered_map<http::HttpStatusCode, std::string> status_code = {
            {http::HttpStatusCode::k200, "200"},
            {http::HttpStatusCode::k403, "403"},
            {http::HttpStatusCode::k404, "404"}};
    } // namespace mapper

} // namespace http