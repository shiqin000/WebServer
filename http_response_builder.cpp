#include "http_response_builder.h"

void http::HttpResponseBuilder::Build(const HttpRequest &http_request, HttpResponse &http_response)
{
    http_response.SetHttpVersion(HttpVersion::HTTP_1_1);
    http_response.SetStatusCode(HttpStatusCode::k200);
    http_response.SetStatusMsg("OK");

    http_response.SetServer("Linux Web Server");

    std::string filename = http_request.uri_;
    if (filename != "index.html")
    {
        BuildError(http_response);
        return;
    }

    filename = "./pages/" + filename;

    size_t index = filename.find_last_of('.');
    if (index == std::string::npos)
        http_response.SetContentType(Mapper::content_type[""]);
    else
        http_response.SetContentType(Mapper::content_type[filename.substr(index)]);

    http_response.SetContentLanguage("zh-CN");

    http_response.SetFilename(filename);
    http_response.SetResponseStr();
}

void http::HttpResponseBuilder::BuildError(HttpResponse &http_response)
{
    http_response.SetHttpVersion(HttpVersion::HTTP_1_1);
    http_response.SetStatusCode(HttpStatusCode::k404);
    http_response.SetStatusMsg("Bad Request");

    http_response.SetServer("Linux Web Server");
    http_response.SetContentType("text/html");
    http_response.SetContentLanguage("zh-CN");

    http_response.SetFilename("404.html");
    http_response.SetResponseStr();
}
