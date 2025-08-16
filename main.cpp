#include <array>
#include <cstdio>
#include <string_view>

#include "pico/stdlib.h"

using namespace std;

struct MorseEntry {
    string_view code;
    char letter;
};

constexpr array<MorseEntry, 26> MORSE_CODE_MAP = {
    {{"01", 'A'},
     {"1000", 'B'},
     {"1010", 'C'},
     {"100", 'D'},
     {"0", 'E'},
     {"0010", 'F'},
     {"110", 'G'},
     {"0000", 'H'},
     {"00", 'I'},
     {"0111", 'J'},
     {"101", 'K'},
     {"0100", 'L'},
     {"11", 'M'},
     {"10", 'N'},
     {"111", 'O'},
     {"0110", 'P'},
     {"1101", 'Q'},
     {"010", 'R'},
     {"000", 'S'},
     {"1", 'T'},
     {"001", 'U'},
     {"0001", 'V'},
     {"011", 'W'},
     {"1001", 'X'},
     {"1011", 'Y'},
     {"1100", 'Z'}}};

char morse_to_char(string_view code) {
    for (auto &[morse, letter] : MORSE_CODE_MAP) {
        if (morse == code) return letter;
    }
    return '?';  // not found default
}

int main() {
    stdio_init_all();  // Initializes USB and UART stdio

    while (true) {
        printf("Pico W is running!\n");
        sleep_ms(1000);
    }

    return 0;
}
