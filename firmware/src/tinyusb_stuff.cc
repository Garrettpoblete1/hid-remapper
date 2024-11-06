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

// Define VID and PID
#define USB_VID 0xCAFE
#define USB_PID 0xBAF2

// Device Descriptor
tusb_desc_device_t desc_device = {
    .bLength = sizeof(tusb_desc_device_t),
    .bDescriptorType = TUSB_DESC_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = 0x00,
    .bDeviceSubClass = 0x00,
    .bDeviceProtocol = 0x00,
    .bMaxPacketSize0 = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor = USB_VID,
    .idProduct = USB_PID,
    .bcdDevice = 0x0100,
    .iManufacturer = 0x01,
    .iProduct = 0x02,
    .iSerialNumber = 0x00,
    .bNumConfigurations = 0x01,
};

// Configuration Descriptors
const uint8_t configuration_descriptor0[] = {
    TUD_CONFIG_DESCRIPTOR(1, 2, 0, TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN + TUD_HID_DESC_LEN, 0, 100),
    TUD_HID_DESCRIPTOR(0, 0, HID_ITF_PROTOCOL_KEYBOARD, our_descriptors[0].descriptor_length, 0x81, CFG_TUD_HID_EP_BUFSIZE, 1),
    TUD_HID_DESCRIPTOR(1, 0, HID_ITF_PROTOCOL_NONE, config_report_descriptor_length, 0x83, CFG_TUD_HID_EP_BUFSIZE, 1),
};

// Other configuration descriptors are defined similarly...

const uint8_t* configuration_descriptors[] = {
    configuration_descriptor0,
    // Add other descriptors as needed
};

char const* string_desc_arr[] = {
    (const char[]){ 0x09, 0x04 },
    "RP2040",
    "HID Remapper XXXX",
};

// Function Prototypes
uint8_t const* tud_descriptor_device_cb();
uint8_t const* tud_descriptor_configuration_cb(uint8_t index);
uint8_t const* tud_hid_descriptor_report_cb(uint8_t itf);
uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);
void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);
void tud_hid_set_protocol_cb(uint8_t instance, uint8_t protocol);
void tud_mount_cb();

// Device Descriptor Callback
uint8_t const* tud_descriptor_device_cb() {
    if ((our_descriptor->

