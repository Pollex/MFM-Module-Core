#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_AverageThreeBytes_should_AverageMidRangeValues(void)
{
  TEST_ASSERT_EQUAL(40, 40);
  TEST_ASSERT_EQUAL(40, 40);
  TEST_ASSERT_EQUAL(33, 40);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_AverageThreeBytes_should_AverageMidRangeValues);
  return UNITY_END();
}