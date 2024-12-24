#define ENCODER_A_PINS { GP27 }
#define ENCODER_B_PINS { GP26 }

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP17 // Specify a optional status led by GPIO number which blinks when entering the bootloader

#define TAPPING_TERM 175

#define MK_3_SPEED
#define MK_W_OFFSET_2 5
#define MK_W_OFFSET_1 3
#define MK_W_OFFSET_0 1