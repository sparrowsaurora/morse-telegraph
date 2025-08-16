#pragma once
#include <cstdint>

#include "pico/stdlib.h"

class Joystick {
   public:
    Joystick(uint x_pin, uint y_pin, uint button_pin, uint16_t deadzone = 10);

    void read();

    int getX() const;
    int getY() const;
    bool isPressed() const;

   private:
    uint x_pin, y_pin, button_pin;
    uint x_channel, y_channel;
    uint16_t center_x, center_y;
    int x_norm = 0, y_norm = 0;
    bool button_pressed = false;
    uint16_t deadzone;

    uint16_t read_adc_raw(uint channel);

    int16_t my_abs(int16_t v);
};
