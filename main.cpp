#include "pico/stdlib.h"
#include <cstdio>

int main() {
    stdio_init_all();
    while (true) {
        printf("Hello Pico!\n");
        sleep_ms(1000);
    }
}
