#include "server.h"

#include "thread_pool.h"
#include "epoll_s.h"

void Server::Run()
{
    Logger::Log(std::string("listening..."));

    int epoll_fd = epoll::Create();
    epoll::AddFd(epoll_fd, server_socket_.GetSockFd(), EPOLLIN | EPOLLET);
    std::vector<epoll_event> epoll_events(epoll::kMaxEvents);
    std::shared_ptr<concurrence::ThreadPool> thread_pool = concurrence::ThreadPool::GetInstance();
    while (true)
    {
        int ret = epoll::Wait(epoll_fd, epoll_events);
        for (int i = 0; i < ret; ++i)
        {
            int sock_fd = epoll_events[i].data.fd;
            if (sock_fd == server_socket_.GetSockFd())
            {
                tcp::ClientSocket client_socket = server_socket_.Accept();
                epoll::AddFd(epoll_fd, client_socket.GetSockFd(), EPOLLIN | EPOLLET);
            }
            else if (epoll_events[i].events & EPOLLIN)
            {
                tcp::ClientSocket client_socket(sock_fd);
                thread_pool->Append(client_socket);
            }
        }
    }

    server_socket_.Close();
}