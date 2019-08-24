//#include "ThreadPoolUnitTest.h"
#include "./ThreadPool.h"

void task_1()
{
    this_thread::sleep_for(std::chrono::milliseconds(80));
}

void task_2()
{
    this_thread::sleep_for(std::chrono::milliseconds(60));
}

void task_3()
{
    this_thread::sleep_for(std::chrono::milliseconds(70));
}

int i = 0;
std::default_random_engine dre;
std::uniform_int_distribution<int> di(20, 50);
std::atomic<int> flag(100);

void task_0()
{
    int n = di(dre);
    this_thread::sleep_for(std::chrono::milliseconds(n));
    //printf("task_0 is running\n");
}

void StartThread()
{
    ThreadPool pool(50);
    pool.Start(12);
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    for (int i = 0; i < 50; i++)
    {
        pool.Set_Task(task_0);
    }
    
    pool.Set_Task(task_1);
    pool.Set_Task(task_2);
    pool.Set_Task(task_3);
    
    this_thread::sleep_for(std::chrono::milliseconds(10000));
    printf("Leave StartThread\n");
}

int main(int argc, char* argv[])
{
    // testing::InitGoogleTest(&argc, argv);
    // RUN_ALL_TESTS();
    StartThread();
    cout << "hello, thread pool" << endl;
    return 0;
}
