#pragma once

#include <pthread.h>
#include "non_copyable.h"
#include "mutex_lock.h"

class Condition : public NonCopyable
{
public:
    explicit Condition(MutexLock &mutex) : mutex_(mutex)
    {
        pthread_cond_init(&cond_, NULL);
    }

    ~Condition()
    {
        pthread_cond_destroy(&cond_);
    }

    void Wait()
    {
        pthread_cond_wait(&cond_, &mutex_.GetMutex());
    }

    void Notify()
    {
        pthread_cond_signal(&cond_);
    }

    void NotifyAll()
    {
        pthread_cond_broadcast(&cond_);
    }

private:
    MutexLock &mutex_;
    pthread_cond_t cond_;
};