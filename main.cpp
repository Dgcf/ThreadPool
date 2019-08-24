#include "ThreadPoolUnitTest.h"

int main(int argc, char* argv[])
{
    // testing::InitGoogleTest(&argc, argv);
    // RUN_ALL_TESTS();
    StartThread();
    cout << "hello, thread pool" << endl;
    return 0;
}
