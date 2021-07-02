#pragma once

#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>

#include "non_copyable.h"

namespace concurrence
{
    // 使用 RAII 机制封装的互斥锁
    class Mutex : public NonCopyable
    {
    public:
        Mutex()
        {
            if (pthread_mutex_init(&mutex_, NULL))
            {
                quick_exit(1);
            }
        }

        ~Mutex()
        {
            if (pthread_mutex_destroy(&mutex_))
            {
                quick_exit(1);
            }
        }

        void Lock()
        {
            if (pthread_mutex_lock(&mutex_))
            {
                quick_exit(1);
            }
        }

        void Unlock()
        {
            if (pthread_mutex_unlock(&mutex_))
            {
                quick_exit(1);
            }
        }

        pthread_mutex_t *GetMutexPointer() { return &mutex_; }

    private:
        pthread_mutex_t mutex_;
    };

    // 使用 RAII 机制封装的信号量
    class Semaphore : public NonCopyable
    {
    public:
        Semaphore()
        {
            if (sem_init(&sem_, 0, 0))
            {
                quick_exit(1);
            }
        }
        ~Semaphore()
        {
            if (sem_destroy(&sem_))
            {
                quick_exit(1);
            }
        }

        void Wait()
        {
            if (sem_wait(&sem_))
            {
                quick_exit(1);
            }
        }

        void Post()
        {
            if (sem_post(&sem_))
            {
                quick_exit(1);
            }
        }

    private:
        sem_t sem_;
    };

    // 使用 RAII 机制封装的条件变量
    class Condition : public NonCopyable
    {
    public:
        explicit Condition(Mutex &mutex) : mutex_(mutex)
        {
            if (pthread_cond_init(&cond_, NULL))
            {
                quick_exit(1);
            }
        }

        ~Condition()
        {
            if (pthread_cond_destroy(&cond_))
            {
                quick_exit(1);
            }
        }

        void Wait()
        {
            if (pthread_cond_wait(&cond_, mutex_.GetMutexPointer()))
            {
                quick_exit(1);
            }
        }

        void Notify()
        {
            if (pthread_cond_signal(&cond_))
            {
                quick_exit(1);
            }
        }

        void NotifyAll()
        {
            if (pthread_cond_broadcast(&cond_))
            {
                quick_exit(1);
            }
        }

    private:
        Mutex &mutex_;
        pthread_cond_t cond_;
    };

} // namespace concurrence
