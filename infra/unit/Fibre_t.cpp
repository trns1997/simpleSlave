#include "gtest/gtest.h"

#include "Fibre.hpp"

#include <iostream>
#include <string>

static std::vector<char> last_fibres;

class FibrePrint : public Fibre
{
    
public :

    FibrePrint(const char* name): Fibre(name)
    {
    }
    virtual void Init()
    {
        last_fibres.push_back(getName()[0]);
    }
    virtual void Run()
    {
        last_fibres.push_back(getName()[0]);
    }
};


bool check_fibres(std::vector<char> expected, std::vector<char> result)
{
    bool res = true;

    for(int i=0; i<result.size(); i++)
    {
        if ( expected[i] != result[i] )
        {
            res = false;
        }
    }
    return res;
}


TEST(ArchTest, test)
{
    FibreManager& thread_polled = FibreManager::getInstance(THREAD_POLLED_ID);
    FibreManager& thread_1ms = FibreManager::getInstance(THREAD_1MS_ID);

    auto fibreA = std::make_shared<FibrePrint>("A");
    auto fibreB = std::make_shared<FibrePrint>("B");
    auto fibreC = std::make_shared<FibrePrint>("C");

    thread_polled.Add(fibreA);
    thread_polled.Add(fibreB);

    thread_1ms.Add(fibreC);
    thread_1ms.Add(fibreB);

    // thread polled
    thread_polled.Init();
    std::vector<char> expected = {'A', 'B'};
    ASSERT_TRUE(check_fibres(expected, last_fibres));
    last_fibres.clear();

    thread_polled.Run();
    expected = {'A', 'B'};
    ASSERT_TRUE(check_fibres(expected, last_fibres));
    last_fibres.clear();

    // thread 1ms
    thread_1ms.Init();
    expected = {'C', 'B'};
    ASSERT_TRUE(check_fibres(expected, last_fibres));
    last_fibres.clear();

    thread_1ms.Run();
    expected = {'C', 'B'};
    ASSERT_TRUE(check_fibres(expected, last_fibres));
    last_fibres.clear();

    // thread mixed
    thread_1ms.Run();
    thread_polled.Run();
    expected = {'C', 'B', 'A', 'B'};
    ASSERT_TRUE(check_fibres(expected, last_fibres));
    last_fibres.clear();

}
