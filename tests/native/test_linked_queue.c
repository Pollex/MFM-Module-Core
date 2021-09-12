#include "unity.h"
#include "os/linked_queue.h"

void setUp(void) {}
void tearDown(void) {}

void nop(void) {}

void test_shouldReturnNULLIfQueueEmpty(void)
{
  os_init();
  TEST_ASSERT_EQUAL_PTR(os_popTask(), NULL);
}

void test_shouldFIFOTasksWithSamePriority(void)
{
  os_init();
  os_task task1 = {
      .func = &nop,
      .priority = 1};
  os_task task2 = {
      .func = &nop,
      .priority = 1};
  os_task task3 = {
      .func = &nop,
      .priority = 1};

  os_pushTask(&task1);
  os_pushTask(&task2);
  os_pushTask(&task3);

  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task1);
  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task2);
  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task3);
}

void test_shouldPrioritizeTaskWithHigherPriority(void)
{
  os_init();
  os_task task1 = {
      .func = &nop,
      .priority = 1};
  os_task task2 = {
      .func = &nop,
      .priority = 1};
  os_task task3 = {
      .func = &nop,
      .priority = 10};

  os_pushTask(&task1);
  os_pushTask(&task2);
  os_pushTask(&task3);

  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task3);
  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task1);
  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task2);
}

void test_shouldPrioritizeTaskInTheMiddle(void)
{
  os_init();
  os_task task1 = {
      .func = &nop,
      .priority = 1};
  os_task task2 = {
      .func = &nop,
      .priority = 2};
  os_task task3 = {
      .func = &nop,
      .priority = 3};

  os_pushTask(&task1);
  os_pushTask(&task2);
  os_pushTask(&task3);

  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task3);
  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task2);
  TEST_ASSERT_EQUAL_PTR(os_popTask(), &task1);
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_shouldReturnNULLIfQueueEmpty);
  RUN_TEST(test_shouldFIFOTasksWithSamePriority);
  RUN_TEST(test_shouldPrioritizeTaskWithHigherPriority);
  RUN_TEST(test_shouldPrioritizeTaskInTheMiddle);
  return UNITY_END();
}