#pragma once

#include <pthread.h>

#include <list>
#include <vector>
#include <memory>

#include "mutex_lock.h"
#include "sem_lock.h"
#include "tcp_socket.h"

// ThreadPool 的实现采用单例模式
class ThreadPool
{
public:
    static std::shared_ptr<ThreadPool> GetInstance() { return instance_; } // 获取 ThreadPool 实例

    ~ThreadPool() { is_stop = true; }

    bool Append(const tcp::ClientSocket &clnt_sock); // 向工作队列添加待处理的套接字

private:
    static constexpr int kDefaultThreadNumber = 8; // 默认分配的工作线程数量
    static constexpr int kMaxThreadNumber = 2048;  // 可分配的工作线程的最大数量
    static constexpr int kMaxRequests = 10000;     // 工作队列中最多允许的等待处理的请求的数量

    ThreadPool();
    explicit ThreadPool(int thread_number);
    ThreadPool(const ThreadPool &) {}
    ThreadPool &operator=(const ThreadPool &) { return *this; }

    static void *Worker(void *arg); // 工作线程的 main 函数

    void Run();
    void CreateThreads(int thread_number); // 创建工作线程组并分离各线程

private:
    int thread_number_;                       // 工作线程的数量
    std::vector<pthread_t> threads_;          // 线程池（线程 ID 的数组）
    std::list<tcp::ClientSocket> work_queue_; // 工作队列（请求队列）
    MutexLock queue_locker_;                  // 保护工作队列专用的互斥锁
    SemLock queue_stat_;                      // 反应工作队列的状态：是否有任务需要处理
    bool is_stop;                             // 是否结束线程，当 is_stop 为 true，线程池中的所有线程都会终止

    static std::shared_ptr<ThreadPool> instance_;
};
