#include "http_response.h"

void http::HttpResponse::SetResponseStr()
{
    response_str_ += "HTTP/1.1";
    response_str_ += ' ';
    response_str_ += mapper::status_code.at(status_code_);
    response_str_ += ' ';
    response_str_ += status_msg_;
    response_str_ += "\r\n";

    response_str_ += "Server:";
    response_str_ += server_;
    response_str_ += "\r\n";

    response_str_ += "Content-Type:";
    response_str_ += content_type_;
    response_str_ += "\r\n";

    response_str_ += "Content-Language:";
    response_str_ += content_language_;
    response_str_ += "\r\n";

    response_str_ += "\r\n";
}