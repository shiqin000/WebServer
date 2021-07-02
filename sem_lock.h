#pragma once

#include <semaphore.h>

#include "non_copyable.h"

class SemLock : public NonCopyable
{
public:
    SemLock()
    {
        if (sem_init(&sem_, 0, 0))
        {
            quick_exit(1);
        }
    }
    ~SemLock()
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
