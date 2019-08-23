#include "ThreadPoolUnitTest.h"

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
}

void StartThread()
{
    ThreadPool pool(15);
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

// class ThreadPoolTest: public testing::Test
// {
// public:
//     ThreadPoolTest(): pool_(18) {}
// protected:
//     virtual void SetUp()
//     {
//         pool_.Start(12);
//     }
//     virtual void TearDown()
//     {

//     }
//     ThreadPool pool_;
// };

// TEST_F(ThreadPoolTest, HandleNoneZeroInput)
// {
//     EXPECT_ANY_THROW(pool_.Set_Task(task_1));
//     EXPECT_ANY_THROW(pool_.Set_Task(task_2));
//     EXPECT_ANY_THROW(pool_.Set_Task(task_3));
// }