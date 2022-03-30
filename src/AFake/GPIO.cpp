#include "gpio.h"

namespace AFake {
namespace {

// Unshadow Arduino functions.
inline void arduino_pinMode(uint32_t dwPin, uint32_t dwMode) { pinMode(dwPin, dwMode); }
inline int arduino_digitalRead(uint32_t ulPin) { return digitalRead(ulPin); }
inline void arduino_digitalWrite(uint32_t dwPin, uint32_t dwVal) { digitalWrite(dwPin, dwVal); }
inline uint32_t arduino_analogRead(uint32_t ulPin) { return analogRead(ulPin); }
inline void arduino_analogWrite( uint32_t ulPin, uint32_t ulValue ) { analogWrite(ulPin, ulValue); }

class RealGPIO : public GPIO {
    public:
        void pinMode(uint32_t dwPin, uint32_t dwMode) override {
            arduino_pinMode(dwPin, dwMode);
        }

        int digitalRead(uint32_t ulPin) override {
            return arduino_digitalRead(ulPin);
        }

        void digitalWrite(uint32_t dwPin, uint32_t dwVal) override {
            arduino_digitalWrite(dwPin, dwVal);
        }

        uint32_t analogRead(uint32_t ulPin) override {
            return arduino_analogRead(ulPin);
        }

        void analogWrite( uint32_t ulPin, uint32_t ulValue ) override {
            arduino_analogWrite(ulPin, ulValue);
        }
};

RealGPIO real_gpio;

}

GPIO* GPIO::real() {
    return &real_gpio;
}

FakeGPIO::FakeGPIO(uint32_t pin_count) {
    pin_values_ = new uint32_t[pin_count]();
    pin_modes_ = new uint32_t[pin_count]();
}

~FakeGPIO() {
    delete pin_values_;
    delete pin_modes_;
}

void FakeGPIO::pinMode(uint32_t dwPin, uint32_t dwMode) {
    pin_modes_[dwPin] = dwMode;
}

// Get the set mode for a pin.
uint32_t FakeGPIO::pinMode(uint32_t dwPin) {
    return pin_modes_[dwPin]; 
}

// Read a digital pin value.
int FakeGPIO::digitalRead(uint32_t ulPin) {
    return pin_values_[ulPin];
}

// Write a digital pin value.
void FakeGPIO::digitalWrite(uint32_t dwPin, uint32_t dwVal) {
    pin_values_[dwPin] =  dwVal;
}

// Read an analog pin value.
uint32_t FakeGPIO::analogRead(uint32_t ulPin) {
    return pin_values_[ulPin];
}

// Write an analog pin value.
void FakeGPIO::analogWrite(uint32_t ulPin, uint32_t ulValue) {
    pin_values_[ulPin] = ulValue;
}

}
