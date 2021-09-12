#include "unity.h"
#include "os/linked_queue.h"

void setUp(void) {}
void tearDown(void) {}

void nop(void) {}

void test_shouldReturnNULLIfQueueEmpty(void)
{
  os_clearTasks();
  TEST_ASSERT_EQUAL_PTR(NULL, os_popTask());
}

void test_shouldFIFOTasksWithSamePriority(void)
{
  os_clearTasks();
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

  TEST_ASSERT_EQUAL_PTR(&task1, os_popTask());
  TEST_ASSERT_EQUAL_PTR(&task2, os_popTask());
  TEST_ASSERT_EQUAL_PTR(&task3, os_popTask());
}

void test_shouldPrioritizeTaskWithHigherPriority(void)
{
  os_clearTasks();
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

  TEST_ASSERT_EQUAL_PTR(&task3, os_popTask());
  TEST_ASSERT_EQUAL_PTR(&task1, os_popTask());
  TEST_ASSERT_EQUAL_PTR(&task2, os_popTask());
}

void test_shouldPrioritizeTaskInTheMiddle(void)
{
  os_clearTasks();
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

  TEST_ASSERT_EQUAL_PTR(&task3, os_popTask());
  TEST_ASSERT_EQUAL_PTR(&task2, os_popTask());
  TEST_ASSERT_EQUAL_PTR(&task1, os_popTask());
}

void test_peekTaskShouldReturnHeadWithoutPopping(void)
{
  os_clearTasks();
  os_task task1 = {
      .func = &nop,
      .priority = 1,
  };

  os_pushTask(&task1);

  TEST_ASSERT_EQUAL_PTR(&task1, os_peekTask());
  TEST_ASSERT_EQUAL_PTR(&task1, os_peekTask());
}

void test_peekTaskShouldReturnNullIfQueueIsEmpty(void)
{
  os_clearTasks();
  TEST_ASSERT_EQUAL_PTR(NULL, os_peekTask());
}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_shouldReturnNULLIfQueueEmpty);
  RUN_TEST(test_shouldFIFOTasksWithSamePriority);
  RUN_TEST(test_shouldPrioritizeTaskWithHigherPriority);
  RUN_TEST(test_shouldPrioritizeTaskInTheMiddle);
  RUN_TEST(test_peekTaskShouldReturnHeadWithoutPopping);
  RUN_TEST(test_peekTaskShouldReturnNullIfQueueIsEmpty);
  return UNITY_END();
}