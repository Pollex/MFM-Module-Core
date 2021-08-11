#if !defined(_EV_EVENTS_H_)
#define _EV_EVENTS_H_

enum events
{
  EV_NONE = 0,

  // TWI events
  EV_SMBUS_ASSERT_CMD,
  EV_SMBUS_CMD,
};

#endif // _EV_EVENTS_H_