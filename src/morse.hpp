#pragma once
#include <string>

/**
 * Converts morsecode to it's char equivelent..
 *
 * @param code the morse code to convert
 * @return returns the char equivelent or a '?' if invalid
 */
char morse_to_char(const std::string &code);

/**
 * Converts a char to it's morse equivelent.
 *
 * @param character the character you wish to convert to morse
 * @return returns the morse code or '?' if invalid
 */
std::string char_to_morse(char c);
