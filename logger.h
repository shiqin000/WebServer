// 作者：xsq
// 文件内容：定义了一个日志记录器
// 文件功能：进行正常运行的日志记录及错误信息记录
#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <memory>

class Logger
{
private:
    Logger() {}
    Logger(const Logger &) {}
    Logger &operator=(const Logger &) { return *this; }

    static std::shared_ptr<Logger> instance_;

public:
    // 获取日志记录器的实例
    static std::shared_ptr<Logger> GetInstance() { return instance_; }

    // 输出指定信息到日志文件中
    static void Log(const std::string &message);

    // 输出指定信息到错误文件中，同时也会输出到日志文件中
    static void Error(const std::string &message);

private:
    // 设置日志文件
    static void SetLogFile(const std::string &log_filename) { Logger::log_filename_ = log_filename; }

    // 设置错误信息文件
    static void SetErrorFile(const std::string &error_filename) { Logger::error_filename_ = error_filename; }

    static std::string GetTime();
    static std::string GetDate();

    static std::string log_filename_;   // 运行日志文件名
    static std::string error_filename_; // 错误信息日志文件名

    static std::ofstream log_ofstream_;   // 负责输出运行日志
    static std::ofstream error_ofstream_; // 负责输出错误信息
};
