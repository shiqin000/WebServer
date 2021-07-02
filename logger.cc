#include "logger.h"

#include <ctime>

std::shared_ptr<Logger> Logger::instance_(new Logger());

std::string Logger::log_filename_("./Log/log.txt");
std::string Logger::error_filename_("./Log/error.txt");

std::ofstream Logger::log_ofstream_ = std::ofstream();
std::ofstream Logger::error_ofstream_ = std::ofstream();

std::string Logger::GetTime()
{
    time_t current_time_int = time(nullptr);
    const tm *current_time_tm_pointer = localtime(&current_time_int);
    std::string current_time_str =
        std::to_string(current_time_tm_pointer->tm_year + 1900) + "/" +
        std::to_string(current_time_tm_pointer->tm_mon + 1) + "/" +
        std::to_string(current_time_tm_pointer->tm_mday) + " " +
        std::to_string(current_time_tm_pointer->tm_hour) + ":" +
        std::to_string(current_time_tm_pointer->tm_min) + ":" +
        std::to_string(current_time_tm_pointer->tm_sec);

    // const char* current_time_str = asctime(current_time_tm_pointer);
    return current_time_str;
}

std::string Logger::GetDate()
{
    time_t current_time_int = time(nullptr);
    const tm *current_time_tm_pointer = localtime(&current_time_int);
    std::string current_date_str =
        std::to_string(current_time_tm_pointer->tm_year + 1900) +
        std::to_string(current_time_tm_pointer->tm_mon + 1) +
        std::to_string(current_time_tm_pointer->tm_mday) + " ";

    return current_date_str;
}

void Logger::Log(const std::string &message)
{
    Logger::SetLogFile("./Log/" + GetDate() + "log.txt");

    log_ofstream_.open(log_filename_, std::ofstream::app);
    Logger::log_ofstream_ << std::setw(22) << std::left << GetTime() << message << std::endl;
    log_ofstream_.close();
}

void Logger::Error(const std::string &message)
{
    Logger::SetErrorFile("./Log/" + GetDate() + "error.txt");

    error_ofstream_.open(error_filename_, std::ofstream::app);
    Logger::error_ofstream_ << std::setw(22) << std::left << GetTime() << message << std::endl;
    error_ofstream_.close();

    Logger::Log(message);
}
