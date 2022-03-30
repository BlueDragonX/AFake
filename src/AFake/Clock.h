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

// A fake implementation of Clock. Allows the user to control the current time
// directly.
class FakeClock : public Clock {
    public:
        FakeClock() : millis_(0) {}

        // Return the current mocked time.
        uint32_t millis() override;

        // Fake a delay. Advances time by ms and returns immediately.
        void delay(uint32_t ms) override;

        // Set the clock to a specific time.
        void set(uint32_t millis);

    private:
        uint32_t millis_;
};

}

#endif  // _AFAKE_CLOCK_H_
