#include "pico/stdlib.h"

int main()
{
    stdio_init_all(); // enable USB serial

    while (true)
    {
        printf("Hello, bare-metal IoT!\n");
        sleep_ms(1000);
    }
}

