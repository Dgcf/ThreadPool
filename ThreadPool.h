#include "./thread.h"

#define DELETE_COPY_CTOR(CLASS) CLASS(const CLASS&) = delete;
#define DELETE_COPY_ASSIGN(CLASS) CLASS& operator=(const CLASS&) = delete;
#define XIAOKA_NO_COPYABLE(CLASS) \
    DELETE_COPY_CTOR(CLASS) \
    DELETE_COPY_ASSIGN(CLASS)

class TestClass
{
public:
    TestClass(int x):i(x){}
    ~TestClass(){cout << "~TestClass: " << i << endl; }

private:
    int i;
};

class ThreadPool
{
public:
    XIAOKA_NO_COPYABLE(ThreadPool)
    typedef std::function<void()> Task; 

public:
    explicit ThreadPool(int taskNum);
    ~ThreadPool();

public:
    void Start(int threadNums);
    void RunInThread();
    void Set_Task(Task task);
    Task Get_task();
    void SetMaxTask(int num) { maxTask_ = num; }

private:
    inline bool isFull() const;
    inline size_t taskQueueSize();
    void Stop();

private:
    std::vector<unique_ptr<Thread>> thread_;
    std::deque<Task> taskQueue_;
    TestClass t3;
    std::condition_variable notFullCond_;
    std::condition_variable notEmptyCond_;
    
    TestClass t2;
    std::mutex mutex_;
    int maxTask_;
    bool running_;
    TestClass t1;
    std::atomic<int> t1_;
    std::atomic<int> t2_;
    std::atomic<bool> exit_;
};