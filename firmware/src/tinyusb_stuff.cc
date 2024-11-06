/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 Jacek Fedorynski
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *

 */

#include <tusb.h>
#include "platform.h" // For GPIO setup
#include "globals.h" // For your global variables

// Define GPIO pins for directional buttons
#define UP_PIN      2
#define DOWN_PIN    3
#define LEFT_PIN    4
#define RIGHT_PIN   5

// Function to read GPIO pin states for directional buttons
void read_directional_inputs(bool *up, bool *down, bool *left, bool *right) {
    *up = gpio_get(UP_PIN);
    *down = gpio_get(DOWN_PIN);
    *left = gpio_get(LEFT_PIN);
    *right = gpio_get(RIGHT_PIN);
}

// SOCD cleaning function
void socd_cleaning(bool *up, bool *down, bool *left, bool *right) {
    // Vertical cleaning: Up + Down = Neutral
    if (*up && *down) {
        *up = false;
        *down = false;
    }
    // Horizontal cleaning: Left + Right = Neutral
    if (*left && *right) {
        *left = false;
        *right = false;
    }
}

// Main function to update USB HID report with cleaned inputs
void send_hid_report() {
    bool up, down, left, right;

    // Read raw input states
    read_directional_inputs(&up, &down, &left, &right);

    // Apply SOCD cleaning
    socd_cleaning(&up, &down, &left, &right);

    // Create a report based on cleaned states
    uint8_t report[4] = {0};
    report[0] = up ? 1 : 0;       // Set bits or values based on the button state
    report[1] = down ? 1 : 0;
    report[2] = left ? 1 : 0;
    report[3] = right ? 1 : 0;

    // Send the report over USB
    tud_hid_report(0, report, sizeof(report));
}

void tud_hid_task() {
    // Check if device is ready to send HID report
    if (tud_hid_ready()) {
        send_hid_report();
    }
}
