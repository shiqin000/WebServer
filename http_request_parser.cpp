#include "http_request_parser.h"

bool http::HttpRequestParser::Parse(char *request_message, HttpRequest &http_request)
{
    bool is_parse_success = true;

    // 分割出请求行并解析请求行
    char *request_line_begin = request_message;
    char *request_line_end = strstr(request_message, "\r\n");
    if (request_line_end == NULL)
        return false;
    *request_line_end++ = '\0';
    *request_line_end++ = '\0';
    is_parse_success = ParseRequestLine(request_line_begin, http_request);
    if (is_parse_success == false)
        return is_parse_success;

    // 分割出首部行并解析首部行
    char *head_lines_begin = request_line_end;
    char *head_lines_end = strstr(head_lines_begin, "\r\n\r\n");
    if (head_lines_end == NULL)
        return false;
    *head_lines_end++ = '\0';
    *head_lines_end++ = '\0';
    *head_lines_end++ = '\0';
    *head_lines_end++ = '\0';
    is_parse_success = ParseHeadLines(head_lines_begin, http_request);
    if (is_parse_success == false)
        return is_parse_success;

    // 分割出消息主体行并解析消息主体
    char *body_lines_begin = head_lines_end;
    is_parse_success = ParseBody(body_lines_begin, http_request);
    return is_parse_success;
}

bool http::HttpRequestParser::ParseRequestLine(char *request_line, HttpRequest &http_request)
{
    // 分割并获取请求方法
    char *method_begin = request_line;
    char *method_end = strchr(request_line, ' ');
    if (method_end == NULL)
        return false;
    *method_end = '\0';
    try
    {
        http_request.request_method_ = Mapper::request_method.at(method_begin);
    }
    catch (const std::exception &e)
    {
        http_request.request_method_ = HttpRequestMethod::METHOD_NOT_SUPPORT;
        Logger::Error("HTTP METHOD NOT SUPPORT");
    }

    // 分割并获取 URI
    char *uri_begin = method_end + 1;
    char *uri_end = strchr(uri_begin, ' ');
    if (uri_end == NULL)
        return false;
    *uri_end = '\0';

    if (*uri_begin == '/')
        ++uri_begin;
    http_request.uri_ = uri_begin;

    // 获取 HTTP 版本
    char *http_version_begin = uri_end + 1;
    try
    {
        http_request.http_version_ = Mapper::http_version.at(http_version_begin);
    }
    catch (const std::exception &e)
    {
        http_request.http_version_ = HttpVersion::VERSION_NOT_SUPPORT;
        Logger::Error("HTTP VERSION NOT SUPPORT");
    }

    return true;
}

bool http::HttpRequestParser::ParseHeadLines(char *head_lines, HttpRequest &http_request)
{
    char *head_begin = head_lines;
    char *head_end = NULL;

    while ((head_end = strstr(head_begin, "\r\n")) != NULL)
    {
        *head_end++ = '\0';
        *head_end++ = '\0';
        if (ParseHeadLine(head_begin, http_request) == false)
            return false;
        head_begin = head_end;
    }

    if (ParseHeadLine(head_begin, http_request) == false)
        return false;

    return true;
}

bool http::HttpRequestParser::ParseBody(char *body_lines, HttpRequest &http_request)
{
    http_request.body_ = body_lines;
    return true;
}

bool http::HttpRequestParser::ParseHeadLine(char *head_line, HttpRequest &http_request)
{
    char *split = strchr(head_line, ':');
    if (split == NULL)
        return false;
    *split++ = '\0';
    std::string head_name = head_line;
    std::string head_val = split;
    http_request.head_group_.insert({head_name, head_val});

    return true;
}