#include "ThreadPoolUnitTest.h"
#include "msgqueue.h"

MsgQueue<string> msg;
std::atomic<int> all_num(0);
void task_1()
{
    string s = msg.take();
    printf("take_1 msg is : %s\n", s.c_str());
    all_num.fetch_add(1);
    this_thread::sleep_for(std::chrono::milliseconds(80));
}
void task_2()
{
    string s = msg.take();
    printf("take_2 msg is : %s\n", s.c_str());
    all_num.fetch_add(1);
    this_thread::sleep_for(std::chrono::milliseconds(60));
}

void task_3()
{
    string s = msg.take();
    printf("take_3 msg is : %s\n", s.c_str());
    all_num.fetch_add(1);
    this_thread::sleep_for(std::chrono::milliseconds(70));
}

void task_0()
{
    string s = msg.take();
    all_num.fetch_add(1);
    printf("task_0 msg is: %s\n", s.c_str());
}

void Add_msg1()
{
    vector<string> vec_msg = {
        "hello", "Zsh", "is", "big", "God", "She", "Very", "Stronge", "But", "Also", "Study", "Hard", "So", "what", "are", "you", "Waiting", "for"
    };
    int size = vec_msg.size();
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0, size-1);
    while (true)
    {
        int index = di(dre);
        printf("english index is: %d\n", index);
        msg.put(vec_msg.at(index));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Add_msg2()
{
    vector<string> vec_msg = {
        "哈啰", "张", "是一位", "大", "神级别", "她是", "非常", "强大", "但是", "也照样", "学习", "努力地", "所以", "什么", "是在", "你", "等待", "为了"
    };
    int size = vec_msg.size();
    std::default_random_engine dre;
    std::uniform_int_distribution<int> di(0, size-1);
    while (true)
    {
        int index = di(dre);
        printf("chinese index is: %d\n", index);
        msg.put(vec_msg.at(index));
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void StartThread()
{
    ThreadPool pool(15);
    pool.Start(12);
    this_thread::sleep_for(std::chrono::milliseconds(1000));
    pool.Set_Task(Add_msg1);
    pool.Set_Task(Add_msg2);
    while (true)
    {
        pool.Set_Task(task_0);
        pool.Set_Task(task_1);
        pool.Set_Task(task_2);
        pool.Set_Task(task_3);
    }
    
    this_thread::sleep_for(std::chrono::milliseconds(10000));
    printf("all num: %d\n", all_num.load());
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