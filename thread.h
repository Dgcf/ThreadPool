#include "../common.h"

class Thread;

void* thread_function(void* th);

class Thread
{
public:
    typedef std::function<void()> ThreadFunc;

public:
    explicit Thread(ThreadFunc, const std::string& name="");
    ~Thread();

    void Start();
    void Join();
    void callback();

private:
    pthread_t   thread_id_;
    ThreadFunc threadfunc_;
    bool start_;
    bool join_;
};
