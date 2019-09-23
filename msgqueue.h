#ifndef GKAI_MSGQUEUE_H
#define GKAI_MSGQUEUE_H

#include <deque>
#include <mutex>
#include <condition_variable>
using namespace std;

template<typename T>
class MsgQueue
{
public:
    MsgQueue(){}

    void put(const T& msg);
    T take();

private:
    T data;
    deque<T>    queue_;
    mutex   readyMutex;
    condition_variable readyCondVar;
};

template<typename T>
void MsgQueue<T>::put(const T& msg)
{
    lock_guard<mutex> lg(readyMutex);
    queue_.push_back(msg);
    readyCondVar.notify_all();
}

template<typename T>
T MsgQueue<T>::take()
{
    unique_lock<mutex> ul(readyMutex);
    readyCondVar.wait(ul, [this]{ return !queue_.empty(); });
    data = queue_.front();
    queue_.pop_front();
    return data;
}


#endif //GKAI_BLOCKINGQUEUE_H