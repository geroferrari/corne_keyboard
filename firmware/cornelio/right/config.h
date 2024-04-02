#pragma once
// Cirque trackpad
// Enable use of pointing device on slave split.
#define SPLIT_POINTING_ENABLE
// Pointing device is on the right split.
#define POINTING_DEVICE_RIGHT
// Adjust trackpad rotation.
#define POINTING_DEVICE_ROTATION_270
// Enables support for extended i16 mouse reports (instead of i8).
#define MOUSE_EXTENDED_REPORT
// Limits the frequency that the sensor is polled for motion.
//#define POINTING_DEVICE_TASK_THROTTLE_MS 10
#define CIRQUE_PINNACLE_DIAMETER_MM 40
#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE
#define POINTING_DEVICE_GESTURES_SCROLL_ENABLE // Circular scroll.
#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_2X
#define CIRQUE_PINNACLE_TAP_ENABLE
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE
