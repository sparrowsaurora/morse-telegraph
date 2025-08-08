//! Blinks the LED on a Pico board
//!
//! This will blink an LED attached to GP25, which is the pin the Pico uses for the on-board LED.
#![no_std]
#![no_main]

use cortex_m::delay::Delay;
use defmt::*;
use defmt_rtt as _;
use embedded_hal::digital::OutputPin;
use pac::{CorePeripherals, Peripherals};
use panic_probe as _;
// Provide an alias for our BSP so we can switch targets quickly.
// Uncomment the BSP you included in Cargo.toml, the rest of the code does not need to change.

use rp_pico as bsp;
// use sparkfun_pro_micro_rp2040 as bsp;
use bsp::{
    entry,
    hal::{
        clocks::{init_clocks_and_plls, Clock, ClocksManager},
        gpio::{bank0::*, FunctionSio, Pin, PullDown, SioOutput},
        pac,
        sio::Sio,
        watchdog::Watchdog,
    },
    Pins,
};

use phf::phf_map;

mod converters;
use crate::converters::*;

/**
 * CONSTANTS
 */

// Use the phf_map! macro to create a static, compile-time map.
// 0 == dot '.'
// 1 == dash '-'
static MORSE_CODE_MAP: phf::Map<&'static str, char> = phf_map! {
    "01" => 'A',
    "1000" => 'B',
    "1010" => 'C',
    "100" => 'D',
    "0" => 'E',
    "0010" => 'F',
    "110" => 'G',
    "0000" => 'H',
    "00" => 'I',
    "0111" => 'J',
    "101" => 'K',
    "0100" => 'L',
    "11" => 'M',
    "10" => 'N',
    "111" => 'O',
    "0110" => 'P',
    "1101" => 'Q',
    "010" => 'R',
    "000" => 'S',
    "1" => 'T',
    "001" => 'U',
    "0001" => 'V',
    "011" => 'W',
    "1001" => 'X',
    "1011" => 'Y',
    "1100" => 'Z',
};

enum Direction {
    Up,
    Down,
    Left,
    Right,
}

fn listen(pins: &Pins) -> Direction {
    let listener_pin: Pin<Gpio25, FunctionSio<SioOutput>, PullDown> =
        pins.led.into_push_pull_output();

    loop {
        let mut paddle_direction: u64 = 0;

        match paddle_direction {
            1..=2 => return Direction::Up,
            3..=4 => return Direction::Down,
            5..=6 => return Direction::Left,
            7..=8 => return Direction::Right,
            _ => {
                info!("how the fuck did you do this???");
                continue;
            }
        }
    }
}

#[entry]
fn main() -> ! {
    info!("Program start");
    let mut pac: Peripherals = Peripherals::take().unwrap();
    let core: CorePeripherals = CorePeripherals::take().unwrap();
    let mut watchdog: Watchdog = Watchdog::new(pac.WATCHDOG);
    let sio: Sio = Sio::new(pac.SIO);

    // External high-speed crystal on the pico board is 12Mhz
    let external_xtal_freq_hz: u32 = 12_000_000u32;
    let clocks: ClocksManager = init_clocks_and_plls(
        external_xtal_freq_hz,
        pac.XOSC,
        pac.CLOCKS,
        pac.PLL_SYS,
        pac.PLL_USB,
        &mut pac.RESETS,
        &mut watchdog,
    )
    .ok()
    .unwrap();

    let mut delay: Delay = Delay::new(core.SYST, clocks.system_clock.freq().to_Hz());

    let pins: Pins = Pins::new(
        pac.IO_BANK0,
        pac.PADS_BANK0,
        sio.gpio_bank0,
        &mut pac.RESETS,
    );

    // let binary: String = String::from("0010 001 1010 101");

    // let result_mrs: String = binary_to_morse(&binary);
    // println!("{}", result_mrs);

    // let result_str: String = binary_to_string(&binary);
    // println!("{}", result_str);

    // This is the correct pin on the Raspberry Pico board. On other boards, even if they have an
    // on-board LED, it might need to be changed.
    //
    // Notably, on the Pico W, the LED is not connected to any of the RP2040 GPIOs but to the cyw43 module instead.
    // One way to do that is by using [embassy](https://github.com/embassy-rs/embassy/blob/main/examples/rp/src/bin/wifi_blinky.rs)
    //
    // If you have a Pico W and want to toggle a LED with a simple GPIO output pin, you can connect an external
    // LED to one of the GPIO pins, and reference that pin here. Don't forget adding an appropriate resistor
    // in series with the LED.
    let mut led_pin: Pin<Gpio25, FunctionSio<SioOutput>, PullDown> =
        pins.led.into_push_pull_output();

    loop {
        listen(pins);
        info!("on!");
        led_pin.set_high().unwrap();
        delay.delay_ms(500);
        info!("off!");
        led_pin.set_low().unwrap();
        delay.delay_ms(500);
    }
}

// End of file
