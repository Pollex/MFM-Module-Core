#include <unity.h>

#define EV_QUEUE_SIZE 5
#include "os/circulair_queue.h"

void setUp() {}
void tearDown() {}

void ev_enableInterrupts()
{
}
void ev_disableInterrupts()
{
}

void test_events_empty_queue_dequeues_NULL(void)
{
  TEST_ASSERT_EQUAL(NULL, ev_dequeue());
}

void test_events_enqueue_dequeue(void)
{
  uint8_t ev1_id = 1;
  uint8_t ev2_id = 2;
  uint8_t ev3_id = 3;
  uint8_t ev4_id = 4;

  ev_enqueue(ev1_id, NULL);
  ev_enqueue(ev2_id, NULL);
  ev_enqueue(ev3_id, NULL);
  ev_enqueue(ev4_id, NULL);

  TEST_ASSERT_EQUAL_MESSAGE(ev1_id, ev_dequeue()->id, "ev_dequeue did not return first event");
  TEST_ASSERT_EQUAL_MESSAGE(ev2_id, ev_dequeue()->id, "ev_dequeue did not return second event");
  TEST_ASSERT_EQUAL_MESSAGE(ev3_id, ev_dequeue()->id, "ev_dequeue did not return third event");
  TEST_ASSERT_EQUAL_MESSAGE(ev4_id, ev_dequeue()->id, "ev_dequeue did not return fourth event");
  TEST_ASSERT_EQUAL_MESSAGE(NULL, ev_dequeue(), "ev_dequeue returned non-NULL at non-existing event");
}

void test_events_pending(void)
{
  TEST_ASSERT_EQUAL(0, ev_pending());

  ev_enqueue(0, NULL);
  TEST_ASSERT_EQUAL(1, ev_pending());

  ev_dequeue();
  TEST_ASSERT_EQUAL(0, ev_pending());

  ev_enqueue(0, NULL);
  ev_enqueue(0, NULL);
  ev_enqueue(0, NULL);
  TEST_ASSERT_EQUAL(1, ev_pending());

  ev_enqueue(0, NULL);
  ev_enqueue(0, NULL);
  ev_enqueue(0, NULL);
  TEST_ASSERT_EQUAL(1, ev_pending());
}

int main(int argc, char **argv)
{
  UNITY_BEGIN();
  RUN_TEST(test_events_empty_queue_dequeues_NULL);
  RUN_TEST(test_events_enqueue_dequeue);
  RUN_TEST(test_events_pending);
  return UNITY_END();
}