#pragma once

#include <string>

#include "http_data_type.h"

namespace http
{
    // HTTP 响应报文（仅包含状态行的内容及除 Content-length 之外的首部）
    class HttpResponse
    {
    public:
        void SetStatusCode(const HttpStatusCode &status_code) { status_code_ = status_code; }
        void SetHttpVersion(const HttpVersion &http_version) { http_version_ = http_version; }
        void SetStatusMsg(const std::string &status_msg) { status_msg_ = status_msg; }

        void SetServer(const std::string &server) { server_ = server; }
        void SetContentType(const std::string &content_type) { content_type_ = content_type; }
        void SetContentLanguage(const std::string &content_language) { content_language_ = content_language; }

        void SetFilename(const std::string &filename) { filename_ = filename; }

        // 构造响应字符串
        void SetResponseStr();

        const std::string GetFilename() const { return filename_; }
        const char *const GetResponseStr() const { return response_str_.c_str(); }

    private:
        // 状态行信息
        HttpStatusCode status_code_;
        HttpVersion http_version_;
        std::string status_msg_;

        // 首部信息(不含 Content-length)
        std::string server_;
        std::string content_type_;
        std::string content_language_;

        // 要发送的文件名
        std::string filename_;

        // 响应字符串
        std::string response_str_;
    };
}
