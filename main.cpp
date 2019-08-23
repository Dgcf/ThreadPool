//#include "ThreadPoolUnitTest.h"
#include "./ThreadPool.h"

void task_1()
{
    cout << "Enter in task_1" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(80));
    cout << "Leave in task_1" << endl;
}

void task_2()
{
    cout << "Enter in task_2" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(60));
    cout << "Leave in task_2" << endl;
}

void task_3()
{
    cout << "Enter in task_3" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(70));
    cout << "Leave in task_3" << endl;
}

int i = 0;
std::default_random_engine dre;
std::uniform_int_distribution<int> di(200, 500);
std::atomic<int> flag(0);

void task_0()
{
    //int n = di(dre);
    //cout << "index is: " << flag.fetch_add(1) << endl;
    //this_thread::sleep_for(std::chrono::milliseconds(n));
    int a = 0;
    int b = a+10;
    printf("Enter in take_0\n");
}

void StartThread()
{
    ThreadPool pool(20);
    pool.Start(12);
    this_thread::sleep_for(std::chrono::milliseconds(6000));
    for (int i = 0; i < 50; i++)
    {
        pool.Set_Task(task_0);
    }
    
    pool.Set_Task(task_1);
    pool.Set_Task(task_2);
    pool.Set_Task(task_3);
}

int main(int argc, char* argv[])
{
    // testing::InitGoogleTest(&argc, argv);
    // RUN_ALL_TESTS();
    StartThread();
    this_thread::sleep_for(std::chrono::milliseconds(120000));
    return 0;
}
