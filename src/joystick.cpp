#include "joystick.hpp"

#include "hardware/adc.h"

Joystick::Joystick(uint x_pin, uint y_pin, uint button_pin, uint16_t deadzone)
    : x_pin(x_pin), y_pin(y_pin), button_pin(button_pin), deadzone(deadzone) {
    // ADC init
    adc_init();
    adc_gpio_init(x_pin);
    adc_gpio_init(y_pin);
    x_channel = x_pin - 26;
    y_channel = y_pin - 26;

    // Button init
    gpio_init(button_pin);
    gpio_set_dir(button_pin, false);  // input
    gpio_pull_up(button_pin);

    // Read initial center values
    center_x = read_adc_raw(x_channel);
    center_y = read_adc_raw(y_channel);
}

void Joystick::read() {
    uint16_t x_val = read_adc_raw(x_channel);
    uint16_t y_val = read_adc_raw(y_channel);

    int16_t x_delta = (int16_t)x_val - center_x;
    int16_t y_delta = (int16_t)y_val - center_y;

    if (abs(x_delta) < deadzone) x_delta = 0;
    if (abs(y_delta) < deadzone) y_delta = 0;

    x_norm = (x_delta * 100) / 2048;
    y_norm = (y_delta * 100) / 2048;

    button_pressed = (gpio_get(button_pin) == 0);
}

int Joystick::getX() const { return x_norm; }
int Joystick::getY() const { return y_norm; }
bool Joystick::isPressed() const { return button_pressed; }

uint16_t Joystick::read_adc_raw(uint channel) {
    adc_select_input(channel);
    return adc_read();
}

int16_t abs(int16_t val) {
    return val < 0 ? -val : val;
}
