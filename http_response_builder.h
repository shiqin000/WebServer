#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "http_data_type.h"
#include "http_request.h"
#include "http_response.h"

namespace http
{
    // HTTP 响应报文构造器
    class HttpResponseBuilder
    {
    public:
        static void Build(const HttpRequest &http_request, HttpResponse &http_response);
        static void BuildError(HttpResponse &http_response);
    };
} // namespace http
