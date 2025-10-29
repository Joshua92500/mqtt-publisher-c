Simple MQTT GPIO publisher in C

Lightweight MQTT publisher that reads a GPIO line using libgpiod and publishes a short message to an MQTT broker using libmosquitto.

Files
- `main.c` - program entry, reads GPIO and publishes MQTT messages in a loop.
- `gpio_reader.c` / `gpio_reader.h` - minimal wrapper around libgpiod for initializing, reading, and closing a Raspberry Pi 5's GPIO line.

Build
Use gcc with libmosquitto and libgpiod libraries included.

Notes
- Change constants `GPIO_LINE` and `MQTT_HOST` in `main.c` before building if needed.
