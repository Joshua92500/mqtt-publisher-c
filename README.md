# Simple MQTT GPIO Publisher in C

A lightweight MQTT publisher written in C that reads a GPIO line using [libgpiod](https://libgpiod.readthedocs.io/) and publishes a message to an MQTT broker using [libmosquitto](https://mosquitto.org/api/files/mosquitto-h.html).

## Files
- `main.c` – Program entry; reads GPIO and publishes MQTT messages in a loop.
- `gpio_reader.c` / `gpio_reader.h` – Minimal wrapper around libgpiod for initializing, reading, and closing a GPIO line.

## Build Instructions
Compile with `gcc`, linking against `libmosquitto` and `libgpiod`.

**Example:**
```bash
gcc main.c gpio_reader.c -o mqtt-publisher -lmosquitto -lgpiod
```

## Configuration
- Edit the constants `GPIO_LINE` and `MQTT_HOST` in `main.c` to match your setup before building.

## Notes
- Designed for Raspberry Pi 5
- Requires `libgpiod` and `libmosquitto` development libraries.
