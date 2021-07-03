#pragma once

#include <sys/epoll.h>
#include <fcntl.h>

#include <memory>
#include <unordered_map>
#include <vector>

#include "logger.h"

namespace epoll
{
    constexpr int kMaxFds = 100000;        // epoll 可监视的最大描述符数量
    constexpr int kMaxEvents = 4096;       // epoll 最多可监听的事件数量
    constexpr int kEpollWaitTime = 100000; // epoll 的超时时间

    void SetNonblocking(int fd)
    {
        int old_option = fcntl(fd, F_GETFL);
        int new_option = old_option | O_NONBLOCK;
        fcntl(fd, F_SETFL, new_option);
    }

    int Create()
    {
        int epoll_fd = epoll_create(5);
        if (epoll_fd == -1)
        {
            Logger::Error("epoll_create() error.");
            quick_exit(1);
        }
        return epoll_fd;
    }

    void AddFd(int epoll_fd, int fd, __uint32_t events)
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = events;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event) < 0)
        {
            Logger::Error("epoll_ctl() error.");
            quick_exit(1);
        }
        SetNonblocking(fd);
    }

    void ModFd(int epoll_fd, int fd, __uint32_t events)
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = events;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &event) < 0)
        {
            Logger::Error("epoll_ctl() error.");
            quick_exit(1);
        }
    }

    void DelFd(int epoll_fd, int fd, __uint32_t events)
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = events;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &event) < 0)
        {
            Logger::Error("epoll_ctl() error.");
            quick_exit(1);
        }
    }

    int Wait(int epoll_fd, std::vector<epoll_event> &epoll_events)
    {
        while (true)
        {
            int event_count = epoll_wait(epoll_fd, &epoll_events[0], epoll_events.size(), kEpollWaitTime);
            if (event_count < 0)
            {
                Logger::Error("epoll_wait() error.");
                quick_exit(1);
            }
            return event_count;
        }
    }

} // namespace epoll