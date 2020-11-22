#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(TCP)
{
  RUN_TEST_CASE(TCP, ServerWrongPort);
  RUN_TEST_CASE(TCP, ClientWrongPort);
}