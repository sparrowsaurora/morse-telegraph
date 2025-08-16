#include "morse.hpp"
#include <array>
#include <string>

struct MorseEntry {
    std::string code;
    char letter;
};

// Fixed-size map of Morse codes
const std::array<MorseEntry, 26> MORSE_CODE_MAP = {{
    {"01", 'A'}, {"1000", 'B'}, {"1010", 'C'}, {"100", 'D'}, {"0", 'E'},
    {"0010", 'F'}, {"110", 'G'}, {"0000", 'H'}, {"00", 'I'}, {"0111", 'J'},
    {"101", 'K'}, {"0100", 'L'}, {"11", 'M'}, {"10", 'N'}, {"111", 'O'},
    {"0110", 'P'}, {"1101", 'Q'}, {"010", 'R'}, {"000", 'S'}, {"1", 'T'},
    {"001", 'U'}, {"0001", 'V'}, {"011", 'W'}, {"1001", 'X'}, {"1011", 'Y'},
    {"1100", 'Z'}
}};

char morse_to_char(const std::string &code) {
    for (auto &[morse, letter] : MORSE_CODE_MAP) {
        if (morse == code) return letter;
    }
    return '?';
}

std::string char_to_morse(char c) {
    for (auto &[morse, letter] : MORSE_CODE_MAP) {
        if (letter == c) return morse;
    }
    return "?";
}
