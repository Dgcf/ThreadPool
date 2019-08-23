#include "./thread.h"

#define DELETE_COPY_CTOR(CLASS) CLASS(const CLASS&) = delete;
#define DELETE_COPY_ASSIGN(CLASS) CLASS& operator=(const CLASS&) = delete;
#define XIAOKA_NO_COPYABLE(CLASS) \
    DELETE_COPY_CTOR(CLASS) \
    DELETE_COPY_ASSIGN(CLASS)

class ThreadPool
{
public:
    XIAOKA_NO_COPYABLE(ThreadPool)
    typedef std::function<void()> Task; 

public:
    explicit ThreadPool(int taskNum);

public:
    void Start(int threadNums);
    void RunInThread();
    void Set_Task(Task task);
    Task Get_task();
    void SetMaxTask(int num) { maxTask_ = num; }

private:
    inline bool isFull() const;
    inline size_t taskQueueSize();

private:
    std::vector<unique_ptr<Thread>> thread_;
    std::deque<Task> taskQueue_;
    std::mutex mutex_;
    std::mutex mutex1_;
    std::mutex mutex2_;
    std::condition_variable notFullCond_;
    std::condition_variable notEmptyCond_;
    int maxTask_;
    bool running_;
    std::atomic<int> t1_;
    std::atomic<int> t2_;
};