#include "./ThreadPool.h"

ThreadPool::ThreadPool(int taskNum):
maxTask_(taskNum),
running_(false),
t1_(0),
t2_(0),
t1(1),
t2(2),
t3(3)
{ }

ThreadPool::~ThreadPool()
{
    //notify_all_at_thread_exit()
}

void ThreadPool::Start(int threadNums)
{
    thread_.reserve(threadNums);
    running_ = true;
    for (int i = 0; i < threadNums; i++)
    {
        thread_.emplace_back(new Thread(std::bind(&ThreadPool::RunInThread, this))); 
        thread_[i]->Start();
    }
}

void ThreadPool::RunInThread()
{
    while (running_)
    {
        Task task(Get_task());
        if(task)
        {
            task();
        }
    }
}

void ThreadPool::Set_Task(Task task)
{
    std::unique_lock<std::mutex> uniquelock(mutex_);
    while (isFull())
    {
        notFullCond_.wait(uniquelock, [this]{return taskQueue_.size()<maxTask_;} );
    }
    
    taskQueue_.push_back(task);
    notEmptyCond_.notify_all();
}

ThreadPool::Task ThreadPool::Get_task()
{
    std::unique_lock<std::mutex> get_lock(mutex_);
    while (taskQueue_.empty())
    {
        notEmptyCond_.wait(get_lock, [this]{  return !taskQueue_.empty(); });
    }

    Task task = taskQueue_.front();
    taskQueue_.pop_front();
    notFullCond_.notify_all();
    return task;
}

bool ThreadPool::isFull() const
{
    return maxTask_ && taskQueue_.size() >= maxTask_;
}

size_t ThreadPool::taskQueueSize()
{
    std::lock_guard<std::mutex> lc(mutex_);
    return taskQueue_.size();
}
