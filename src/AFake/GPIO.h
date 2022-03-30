#ifndef _AFAKE_GPIO_H_
#define _AFAKE_GPIO_H_

#include <Arduino.h>

namespace AFake {

// Base GPIO interface. Allows GPIO interaction to be faked.
class GPIO {
    public:
        // Return the real GPIO interface.
        static GPIO* real();

        GPIO() = default;
        virtual ~GPIO() = default;

        // Set the pin mode.
        virtual void pinMode(uint32_t dwPin, uint32_t dwMode) = 0;

        // Read a digital pin value.
        virtual int digitalRead(uint32_t ulPin) = 0;

        // Write a digital pin value.
        virtual void digitalWrite(uint32_t dwPin, uint32_t dwVal) = 0;

        // Read an analog pin value.
        virtual uint32_t analogRead(uint32_t ulPin) = 0;

        // Write an analog pin value.
        virtual void analogWrite(uint32_t ulPin, uint32_t ulValue) = 0;
};

// A fake implementation of GPIO. Allows the caller to directly control the
// values returned by GPIO pins.
class FakeGPIO : public GPIO {
    public:
        // Create a new fake. Allocates space to store GPIO values 32 pins.
        // The pin_count arg can be passed to change this if your board has
        // more pins or you want to conserve memory when running tests on an
        // actual board.
        explicit FakeGPIO(uint32_t pin_count = 32);

        // Frees the fake's internal pin storage.
        ~FakeGPIO() override;

        // Set the pin mode.
        void pinMode(uint32_t dwPin, uint32_t dwMode) override;

        // Get the set mode for a pin.
        uint32_t pinMode(uint32_t dwPin);

        // Read a digital pin value.
        int digitalRead(uint32_t ulPin) override;

        // Write a digital pin value.
        void digitalWrite(uint32_t dwPin, uint32_t dwVal) override;

        // Read an analog pin value.
        uint32_t analogRead(uint32_t ulPin) override;

        // Write an analog pin value.
        void analogWrite(uint32_t ulPin, uint32_t ulValue) override;
    private:
        uint32_t* pin_values_;
        uint32_t* pin_modes_;
};

}

#endif  // _AFAKE_GPIO_H_
