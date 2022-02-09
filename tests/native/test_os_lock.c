#include "unity.h"
#include "os/lock.h"

void test_shouldBeBusyIfLocked(void)
{
  TEST_ASSERT_EQUAL(0, os_hasLock());
  os_lock(os_lock_twi);
  TEST_ASSERT_EQUAL(1, os_hasLock());
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_shouldBeBusyIfLocked);
  return UNITY_END();
}