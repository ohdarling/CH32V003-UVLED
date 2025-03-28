/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 */
/*
 * SSD1306xLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x64 displays
 *
 * @created: 2014-08-12
 * @author: Neven Boyanov
 *
 * Source code available at: https://bitbucket.org/tinusaur/ssd1306xled
 *
 */

// ----------------------------------------------------------------------------

#include <stdint.h>

// ----------------------------------------------------------------------------

/* Font Information:
 * Modern DOS is a raster monospace serif based on IBM and Verite, extracted from VGA ROM typefaces
 * in real machines by various manufacturers, created with FontForge.
 * Source files available on NotABug: https://notabug.org/HarvettFox96/ttf-moderndos
 *
 * This typeface is made by Jayvee Enaguas (HarvettFox96), licensed under a Creative Commons Zero
 * (CC0) 1.0. © 2009-2018.
 */

const uint8_t ssd1306xled_font8x16mdos [] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x38, 0xfc, 0xfc, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x0d, 0x00, 0x00, 0x00,
    0x00, 0x06, 0x1e, 0x00, 0x00, 0x06, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0xf0, 0xf0, 0x40, 0xf0, 0xf0, 0x40, 0x00, 0x02, 0x0f, 0x0f, 0x02, 0x0f, 0x0f, 0x02, 0x00,
    0x30, 0x78, 0xc8, 0xfe, 0x88, 0x38, 0x30, 0x00, 0x06, 0x0e, 0x08, 0x3f, 0x09, 0x0f, 0x06, 0x00,
    0x18, 0x24, 0xa4, 0xd8, 0x60, 0x30, 0x18, 0x00, 0x06, 0x03, 0x01, 0x06, 0x09, 0x09, 0x06, 0x00,
    0x00, 0x98, 0xfc, 0xe4, 0x3c, 0x98, 0x80, 0x00, 0x07, 0x0f, 0x08, 0x09, 0x07, 0x0f, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x16, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xf0, 0xf8, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0c, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x0c, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0c, 0x07, 0x03, 0x00, 0x00,
    0x80, 0xa0, 0xe0, 0xc0, 0xc0, 0xe0, 0xa0, 0x80, 0x00, 0x02, 0x03, 0x01, 0x01, 0x03, 0x02, 0x00,
    0x00, 0x80, 0x80, 0xe0, 0xe0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2c, 0x1c, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x00, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xf8, 0xfc, 0x84, 0xc4, 0x64, 0xfc, 0xf8, 0x00, 0x07, 0x0f, 0x09, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0x00, 0x10, 0x18, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x00,
    0x08, 0x0c, 0x84, 0xc4, 0x64, 0x3c, 0x18, 0x00, 0x0e, 0x0f, 0x09, 0x08, 0x08, 0x0c, 0x0c, 0x00,
    0x08, 0x0c, 0x44, 0x44, 0x44, 0xfc, 0xb8, 0x00, 0x04, 0x0c, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0xc0, 0xe0, 0x30, 0x18, 0xfc, 0xfc, 0x00, 0x00, 0x01, 0x01, 0x01, 0x09, 0x0f, 0x0f, 0x09, 0x00,
    0x7c, 0x7c, 0x44, 0x44, 0x44, 0xc4, 0x84, 0x00, 0x04, 0x0c, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0xf8, 0xfc, 0x44, 0x44, 0x44, 0xcc, 0x88, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0x0c, 0x0c, 0x04, 0x84, 0xc4, 0x7c, 0x3c, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00,
    0xb8, 0xfc, 0x44, 0x44, 0x44, 0xfc, 0xb8, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0x78, 0xfc, 0x84, 0x84, 0x84, 0xfc, 0xf8, 0x00, 0x04, 0x0c, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x16, 0x0e, 0x00, 0x00, 0x00,
    0x00, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x08, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x08, 0x00,
    0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
    0x00, 0x08, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x08, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00,
    0x18, 0x1c, 0x04, 0x84, 0xc4, 0x7c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x0d, 0x00, 0x00, 0x00,
    0xe0, 0x10, 0xc8, 0x28, 0x28, 0xe8, 0x10, 0xe0, 0x03, 0x04, 0x0b, 0x0a, 0x09, 0x0b, 0x02, 0x01,
    0xf0, 0xf8, 0x8c, 0x84, 0x8c, 0xf8, 0xf0, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00,
    0x04, 0xfc, 0xfc, 0x44, 0x44, 0xfc, 0xb8, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0xf8, 0xfc, 0x04, 0x04, 0x04, 0x1c, 0x18, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0e, 0x06, 0x00,
    0x04, 0xfc, 0xfc, 0x04, 0x04, 0xfc, 0xf8, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0x04, 0xfc, 0xfc, 0xc4, 0xe4, 0x0c, 0x1c, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x09, 0x0c, 0x0e, 0x00,
    0x04, 0xfc, 0xfc, 0xc4, 0xe4, 0x0c, 0x1c, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x01, 0x00, 0x00, 0x00,
    0xf8, 0xfc, 0x04, 0x04, 0x84, 0x9c, 0x98, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x0f, 0x00,
    0xfc, 0xfc, 0x40, 0x40, 0x40, 0xfc, 0xfc, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00,
    0x00, 0x00, 0x04, 0xfc, 0xfc, 0x04, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x04, 0xfc, 0xfc, 0x04, 0x00, 0x06, 0x0e, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x00,
    0x04, 0xfc, 0xfc, 0xc0, 0xe0, 0x3c, 0x1c, 0x00, 0x08, 0x0f, 0x0f, 0x00, 0x01, 0x0f, 0x0e, 0x00,
    0x04, 0xfc, 0xfc, 0x04, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x08, 0x0c, 0x0e, 0x00,
    0xfc, 0xf8, 0x70, 0xe0, 0x70, 0xf8, 0xfc, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00,
    0xfc, 0xf8, 0x70, 0xe0, 0xc0, 0xfc, 0xfc, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x01, 0x0f, 0x0f, 0x00,
    0xf8, 0xfc, 0x04, 0x04, 0x04, 0xfc, 0xf8, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0x04, 0xfc, 0xfc, 0x84, 0x84, 0xfc, 0x78, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x00,
    0xf8, 0xfc, 0x04, 0x04, 0x04, 0xfc, 0xf8, 0x00, 0x07, 0x0f, 0x08, 0x0e, 0x0c, 0x1f, 0x17, 0x00,
    0x04, 0xfc, 0xfc, 0x84, 0x84, 0xfc, 0x78, 0x00, 0x08, 0x0f, 0x0f, 0x00, 0x01, 0x0f, 0x0e, 0x00,
    0x18, 0x3c, 0x64, 0x44, 0xc4, 0x9c, 0x18, 0x00, 0x06, 0x0e, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0x00, 0x1c, 0x0c, 0xfc, 0xfc, 0x0c, 0x1c, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00,
    0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0xfc, 0xfc, 0x00, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x06, 0x03, 0x01, 0x00,
    0xfc, 0xfc, 0x00, 0x80, 0x00, 0xfc, 0xfc, 0x00, 0x0f, 0x07, 0x03, 0x01, 0x03, 0x07, 0x0f, 0x00,
    0x0c, 0x3c, 0xf0, 0xe0, 0xf0, 0x3c, 0x0c, 0x00, 0x0c, 0x0f, 0x03, 0x01, 0x03, 0x0f, 0x0c, 0x00,
    0x00, 0x3c, 0x7c, 0xc0, 0xc0, 0x7c, 0x3c, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00,
    0x1c, 0x0c, 0x84, 0xc4, 0x64, 0x3c, 0x1c, 0x00, 0x0e, 0x0f, 0x09, 0x08, 0x08, 0x0c, 0x0e, 0x00,
    0x00, 0x00, 0xfc, 0xfc, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x08, 0x08, 0x00, 0x00,
    0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x00,
    0x00, 0x00, 0x04, 0x04, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x0f, 0x0f, 0x00, 0x00,
    0x20, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x00, 0x00, 0x00, 0x0e, 0x16, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xa0, 0xa0, 0xa0, 0xe0, 0xc0, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x07, 0x0f, 0x08, 0x00,
    0x04, 0xfc, 0xfc, 0x20, 0x20, 0xe0, 0xc0, 0x00, 0x00, 0x0f, 0x0f, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0xc0, 0xe0, 0x20, 0x20, 0x20, 0x60, 0x40, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0c, 0x04, 0x00,
    0xc0, 0xe0, 0x20, 0x24, 0xfc, 0xfc, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x07, 0x0f, 0x08, 0x00,
    0xc0, 0xe0, 0x20, 0x20, 0x20, 0xe0, 0xc0, 0x00, 0x07, 0x0f, 0x09, 0x09, 0x09, 0x0d, 0x05, 0x00,
    0x00, 0x20, 0xf8, 0xfc, 0x24, 0x2c, 0x08, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00, 0x00,
    0xc0, 0xe0, 0x20, 0x20, 0xc0, 0xe0, 0x20, 0x00, 0x27, 0x6f, 0x48, 0x48, 0x7f, 0x3f, 0x00, 0x00,
    0x04, 0xfc, 0xfc, 0x40, 0x20, 0xe0, 0xc0, 0x00, 0x08, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00,
    0x00, 0x00, 0x20, 0xec, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x20, 0xec, 0xec, 0x00, 0x00, 0x30, 0x70, 0x40, 0x40, 0x7f, 0x3f, 0x00, 0x00,
    0x04, 0xfc, 0xfc, 0x80, 0xc0, 0x60, 0x20, 0x00, 0x08, 0x0f, 0x0f, 0x01, 0x03, 0x0e, 0x0c, 0x00,
    0x00, 0x00, 0x04, 0xfc, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00,
    0xe0, 0xe0, 0x60, 0xc0, 0x60, 0xe0, 0xc0, 0x00, 0x0f, 0x0f, 0x00, 0x07, 0x00, 0x0f, 0x0f, 0x00,
    0x20, 0xe0, 0xc0, 0x20, 0x20, 0xe0, 0xc0, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00,
    0xc0, 0xe0, 0x20, 0x20, 0x20, 0xe0, 0xc0, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x08, 0x0f, 0x07, 0x00,
    0x20, 0xe0, 0xc0, 0x20, 0x20, 0xe0, 0xc0, 0x00, 0x40, 0x7f, 0x7f, 0x48, 0x08, 0x0f, 0x07, 0x00,
    0xc0, 0xe0, 0x20, 0x20, 0xe0, 0xe0, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x48, 0x7f, 0x7f, 0x40, 0x00,
    0x20, 0xe0, 0xc0, 0x60, 0x20, 0x60, 0x60, 0x00, 0x08, 0x0f, 0x0f, 0x08, 0x00, 0x00, 0x00, 0x00,
    0x40, 0xe0, 0xa0, 0x20, 0x20, 0x60, 0x40, 0x00, 0x04, 0x0c, 0x09, 0x09, 0x0b, 0x0e, 0x04, 0x00,
    0x20, 0x20, 0xf8, 0xfc, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x04, 0x00, 0x00,
    0xe0, 0xe0, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x07, 0x0f, 0x08, 0x00,
    0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x06, 0x03, 0x01, 0x00,
    0xe0, 0xe0, 0x00, 0xc0, 0x00, 0xe0, 0xe0, 0x00, 0x07, 0x0f, 0x0c, 0x07, 0x0c, 0x0f, 0x07, 0x00,
    0x60, 0xe0, 0x80, 0x00, 0x80, 0xe0, 0x60, 0x00, 0x0c, 0x0e, 0x03, 0x01, 0x03, 0x0e, 0x0c, 0x00,
    0xe0, 0xe0, 0x00, 0x00, 0x00, 0xe0, 0xe0, 0x00, 0x47, 0x4f, 0x48, 0x48, 0x68, 0x3f, 0x1f, 0x00,
    0x60, 0x20, 0x20, 0xa0, 0xe0, 0x60, 0x20, 0x00, 0x0c, 0x0e, 0x0b, 0x09, 0x08, 0x08, 0x0c, 0x00,
    0x00, 0x40, 0x40, 0xf8, 0xbc, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x07, 0x0f, 0x08, 0x08, 0x00,
    0x00, 0x00, 0x00, 0x3c, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x04, 0xbc, 0xf8, 0x40, 0x40, 0x00, 0x00, 0x08, 0x08, 0x0f, 0x07, 0x00, 0x00, 0x00,
    0x08, 0x0c, 0x04, 0x0c, 0x08, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


// ----------------------------------------------------------------------------

const DCfont TinyOLED4kfont8x16mdos = {
  (uint8_t *)ssd1306xled_font8x16mdos,
  8, // character width in pixels
  2, // character height in pages (8 pixels)
  32,126 // ASCII extents
  };

// for backwards compatibility
#define FONT8X16MDOS (&TinyOLED4kfont8x16mdos)
