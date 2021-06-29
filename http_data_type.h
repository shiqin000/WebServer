#pragma once

#include "unordered_map"

namespace http
{
    const int kBufferSize = 1024;

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

    struct Mapper
    {
        static std::unordered_map<std::string, HttpRequestMethod> request_method;
        static std::unordered_map<std::string, HttpVersion> http_version;
        static std::unordered_map<std::string, HttpHead> head;
        static std::unordered_map<std::string, std::string> content_type;
        static std::unordered_map<HttpStatusCode, std::string> status_code;
    };

}