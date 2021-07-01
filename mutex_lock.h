#pragma once

#include <pthread.h>
#include "non_copyable.h"
#include "logger.h"

class MutexLock : public NonCopyable
{
public:
    MutexLock()
    {
        if (pthread_mutex_init(&mutex_, NULL) != 0)
        {
            exit(1);
        }
    }

    ~MutexLock()
    {
        if (pthread_mutex_destroy(&mutex_) != 0)
        {
            exit(1);
        }
    }

    void Lock()
    {
        if (pthread_mutex_lock(&mutex_) != 0)
        {
            exit(1);
        }
    }

    void Unlock()
    {
        if (pthread_mutex_unlock(&mutex_) != 0)
        {
            exit(1);
        }
    }

    pthread_mutex_t GetMutex() { return mutex_; }

private:
    pthread_mutex_t mutex_;
};