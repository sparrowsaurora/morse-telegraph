pub mod converters {
    /**
     * CONVERTERS
     */

    pub fn binary_to_morse(binary: &String) -> String {
        let mut morse_vec: Vec<char> = Vec::new();
        for press in binary.chars() {
            match press {
                '1' => morse_vec.push('-'),
                '0' => morse_vec.push('.'),
                ' ' => morse_vec.push('/'),
                _ => println!("Could not find a code for '{}'", press),
            }
        }
        let return_string: String = morse_vec.into_iter().collect();
        return_string
    }

    pub fn morse_to_binary(morse: &String) -> String {
        let mut binary_vec: Vec<char> = Vec::new();
        for press in morse.chars() {
            match press {
                '-' => binary_vec.push('1'),
                '.' => binary_vec.push('0'),
                '/' => binary_vec.push(' '),
                _ => println!("Could not find a code for '{}'", press),
            }
        }
        let return_string: String = binary_vec.into_iter().collect();
        return_string
    }

    pub fn binary_to_string(binary: &String) -> String {
        let mut string_vec: Vec<char> = Vec::new();
        for press in binary.split(" ") {
            if let Some(code) = MORSE_CODE_MAP.get(press) {
                string_vec.push(*code);
            } else {
                println!("Could not find a code for '{}'", press);
            }
        }
        let return_string: String = string_vec.into_iter().collect();
        return_string
    }
}
