#ifndef _AFAKE_CLOCK_H_
#define _AFAKE_CLOCK_H_

#include <Arduino.h>

namespace AFake {

// Base clock interface. Allows the clock to be mocked.
class Clock {
    public:
        // Return a real clock.
        static Clock* real();

        Clock() = default;
        virtual ~Clock() = default;

        // Return the number of milliseconds since the Arduino started.
        virtual uint32_t millis() = 0;

        // Pause the Arduino for the given number of milliseconds.
        virtual void delay(uint32_t) = 0;
};

}

#endif  // _AFAKE_CLOCK_H_
