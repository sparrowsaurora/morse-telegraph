#include "pico/stdlib.h"
#include <cstdio>

int main() {
    stdio_init_all();  // Initializes USB and UART stdio

    while (true) {
        printf("Pico W is running!\n");
        sleep_ms(1000);
    }
}
