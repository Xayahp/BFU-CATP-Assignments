#include "test1.h"

#include "lib/mathlib.h"
#include "vector"

#include <thread>
#include <iostream>

#include "tbb/parallel_for.h"

void HinaPE::TEST::Test1::test()
{
    std::atomic counter = 0;
    std::thread t1([&]()
                   {
                       for (int i = 0; i < 10000; i++)
                       {
                           counter++;
                       }
                   });
    std::thread t2([&]()
                   {
                       for (int i = 0; i < 10000; i++)
                       {
                           counter++;
                       }
                   });
    t1.join();
    t2.join();
    std::cout << counter << std::endl;
}