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
#include "config.h"
#include "globals.h"
#include "our_descriptor.h"
#include "platform.h"
#include "remapper.h"

// Include the correct header for GPIO functions on the RP2040
#include "pico/stdlib.h"

// Device Descriptor Callback
uint8_t const* tud_descriptor_device_cb() {
    if ((our_descriptor->vid != 0) && (our_descriptor->pid != 0)) {
        desc_device.idVendor = our_descriptor->vid;
        desc_device.idProduct = our_descriptor->pid;
    }
    return (uint8_t const*)&desc_device;
}

// Example usage of setting array_count with an explicit cast to avoid narrowing conversion warning
void set_mapping_from_config() {
    map_source_t map_src = {
        .array_count = static_cast<uint8_t>(array_usage.usage_def.count) // Casting to avoid narrowing warning
    };

    // Other configuration setup code
}

// Read input range with type-matching in conditional to avoid signed-unsigned comparison warning
void read_input_range(const uint8_t* buffer, int buffer_length, uint32_t bits, const usage_def_t& their_usage, uint8_t min, uint8_t max) {
    if ((static_cast<int32_t>(bits) >= their_usage.logical_minimum) &&
        (static_cast<int32_t>(bits) <= their_usage.logical_maximum)) {
        // Code to process the range within limits
    }
}

// Monitor input range with type-matching to prevent signed-unsigned comparison warnings
void monitor_read_input_range(const uint8_t* buffer, int buffer_length, uint32_t bits, const usage_def_t& their_usage, uint8_t min, uint8_t max) {
    if ((static_cast<int32_t>(bits) >= their_usage.logical_minimum) &&
        (static_cast<int32_t>(bits) <= their_usage.logical_maximum)) {
        // Code to process the range within limits
    }
}

// Optimizing expressions with initialized prev_elem to avoid uninitialized variable warnings
void optimize_expressions() {
    element_type prev_elem = {}; // Initialize to avoid potential uninitialized usage

    // Optimization code
    if (prev_elem.op == Op::PUSH_USAGE) {
        // Code block for specific operation
    }
}

// Example function demonstrating GPIO usage on RP2040
void read_directional_inputs(bool* up, bool* down, bool* left, bool* right) {
    *up = gpio_get(UP_PIN);
    *down = gpio_get(DOWN_PIN);
    *left = gpio_get(LEFT_PIN);
    *right = gpio_get(RIGHT_PIN);
}
