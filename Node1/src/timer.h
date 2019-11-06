#ifndef TIMER_H
#define TIMER_H

#include <stdbool.h>

// Flash heartbeat with 1 Hz
#define HEARTBEAT_FREQ      60

// Send joystick with 10 Hz
#define CAN_FREQ            6

void timer_init(void);
bool timer_get_oled_timeout(void);
bool timer_get_heartbeat_timeout(void);
bool timer_get_can_timeout(void);

#endif // TIMER_H