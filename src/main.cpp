#include <iostream>
#include <tuple>

#include "hardware/adc.h"
#include "morse.hpp"
#include "pico/stdlib.h"

enum Direction {
    Up,
    Down,
    Left,
    Right,
    Center,
};

void print(uint x_val, uint y_val) {
    std::cout << "X: " << x_val
              << " | Y: " << y_val
              << std::endl;
}

Direction get_direction(uint x_val, uint y_val) {
    if (x_val < 1500)
        return Direction::Left;
    else if (x_val > 2500)
        return Direction::Right;

    if (y_val < 1500)
        return Direction::Down;
    else if (y_val > 2500)
        return Direction::Up;

    return Direction::Center;
}

void setup() {
    stdio_init_all();  // Init USB / UART

    // Init ADC hardware
    adc_init();
    adc_gpio_init(26);  // map VRx to gpio26
    // adc_select_input(0);  // Select channel 0
    adc_gpio_init(27);  // map VRy to gpio27

    // Tnitialise the power button
    // NOT IMPLEMENTED

    std::cout << "Setup Complete." << std::endl;
}

int main() {
    setup();

    // ADC chanels
    const uint X_CHANNEL = 0;
    const uint Y_CHANNEL = 1;

    while (true) {
        // Read analog joystick positions
        adc_select_input(X_CHANNEL);
        uint16_t x_val = adc_read();  // 0 - 4095
        adc_select_input(Y_CHANNEL);
        uint16_t y_val = adc_read();  // 0 - 4095

        print(x_val, y_val);

        // Test conversions
        // std::cout << "C -> " << char_to_morse('C') << std::endl;        // "1010"
        // std::cout << "1010 -> " << morse_to_char("1010") << std::endl;  // 'C'

        sleep_ms(200);
    }
}
