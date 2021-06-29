#include "http_data_type.h"

std::unordered_map<std::string, http::HttpRequestMethod> http::Mapper::request_method = {
    {"GET", http::HttpRequestMethod::GET},
    {"POST", http::HttpRequestMethod::POST},
    {"PUT", http::HttpRequestMethod::PUT},
    {"HEAD", http::HttpRequestMethod::HEAD},
    {"DELETE", http::HttpRequestMethod::DELETE}};

std::unordered_map<std::string, http::HttpVersion> http::Mapper::http_version = {
    {"HTTP/1.0", http::HttpVersion::HTTP_1_0},
    {"HTTP/1.1", http::HttpVersion::HTTP_1_1}};

std::unordered_map<std::string, http::HttpHead>
    http::Mapper::head = {};

std::unordered_map<std::string, std::string> http::Mapper::content_type = {
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

std::unordered_map<http::HttpStatusCode, std::string> http::Mapper::status_code = {
    {http::HttpStatusCode::k200, "200"},
    {http::HttpStatusCode::k403, "403"},
    {http::HttpStatusCode::k404, "404"}};
