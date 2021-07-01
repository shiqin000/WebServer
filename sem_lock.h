#pragma once

#include <semaphore.h>
#include "non_copyable.h"

class SemLock : public NonCopyable
{
public:
    SemLock()
    {
        if (sem_init(&sem_, 0, 0) != 0)
        {
            exit(1);
        }
    }
    ~SemLock()
    {
        sem_destroy(&sem_);
    }

    void Wait()
    {
        sem_wait(&sem_);
    }

    void Post()
    {
        sem_post(&sem_);
    }

private:
    sem_t sem_;
};
