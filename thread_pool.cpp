#include "thread_pool.h"

const int ThreadPool::kMaxThreadNumber = 2048;
const int ThreadPool::kMaxRequests = 10000;

ThreadPool::ThreadPool(int thread_number) : thread_number_(thread_number), is_stop(false)
{
    if (thread_number <= 0 || thread_number > kMaxThreadNumber)
    {
        thread_number_ = 8;
    }

    threads_.resize(thread_number_);

    for (int i = 0; i < thread_number_; ++i)
    {
        if (pthread_create(&threads_[i], NULL, Worker, this) != 0)
        {
            exit(1);
        }

        // 分离线程
        if (pthread_detach(threads_[i]) != 0)
        {
            exit(1);
        }
    }
}

ThreadPool::~ThreadPool()
{
    is_stop = true;
}

bool ThreadPool::Append(const tcp::ClientSocket &clnt_sock)
{
    // 对工作队列的操作需要加锁（工作队列是多个线程的共享数据）
    queue_locker_.Lock();
    if (work_queue_.size() > static_cast<size_t>(kMaxRequests))
    {
        queue_locker_.Unlock();
        return false;
    }
    work_queue_.push_back(clnt_sock);
    queue_locker_.Unlock();

    queue_stat_.Post(); // 将信号量 +1，以唤醒沉睡中的工作线程

    return true;
}

void *ThreadPool::Worker(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;
    pool->Run();
    return pool;
}

void ThreadPool::Run()
{
    while (!is_stop)
    {
        queue_stat_.Wait();
        queue_locker_.Lock();
        if (work_queue_.empty())
        {
            queue_locker_.Unlock();
            continue;
        }
        tcp::ClientSocket clnt_sock = work_queue_.front();
        work_queue_.pop_front();
        queue_locker_.Unlock();
        clnt_sock.Process();
    }
}