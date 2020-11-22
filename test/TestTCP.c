#include "TCP.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(TCP);

/* These should be ignored because they are commented out in various ways:
#include "whatever.h"
*/
//#include "somethingelse.h"

TEST_SETUP(TCP)
{
}

TEST_TEAR_DOWN(TCP)
{
}

TEST(TCP, IgnoredTest)
{
    TEST_IGNORE_MESSAGE("This Test Was Ignored On Purpose");
}

TEST(TCP, AnotherIgnoredTest)
{
    TEST_IGNORE_MESSAGE("These Can Be Useful For Leaving Yourself Notes On What You Need To Do Yet");
}

TEST(TCP, ThisFunctionHasNotBeenTested_NeedsToBeImplemented)
{
    TEST_IGNORE(); //Like This
}
