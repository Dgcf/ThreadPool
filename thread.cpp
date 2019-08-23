#include "./thread.h"

void* thread_function(void* th)
{
    Thread* ptr = static_cast<Thread*>(th);
    ptr->callback();
}

Thread::Thread(ThreadFunc func, const std::string& name):
thread_id_(0),
threadfunc_(func),
start_(false)
{
}

Thread::~Thread()
{
    if (start_)
    {
        pthread_detach(thread_id_);
        start_ = false;
    }
}

void Thread::Start()
{
    if(0 == pthread_create(&thread_id_, NULL, thread_function, (void*)this))
    {
        start_ = true;
    }
}

void Thread::Join()
{
    if (!join_)
    {
        pthread_join(thread_id_, NULL);
    }
}

void Thread::callback()
{
    threadfunc_();
}