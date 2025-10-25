#include "gpio_reader.h"
#include <gpiod.h>

static struct gpiod_chip *chip = NULL;
static struct gpiod_line *line_handle = NULL;

int gpio_init(int line_num)
{
	chip = gpiod_chip_open_by_name("gpiochip0");
	if (!chip) return -1;

	line_handle = gpiod_chip_get_line(chip, line_num);
	if (!line_handle) return -1;

	if (gpiod_line_request_input(line_handle, "mqtt-publisher") < 0) return -1;

	return 0;
}

int gpio_read(void)
{
	if (!line_handle) return -1;
	int v = gpiod_line_get_value(line_handle);
	return v;
}

void gpio_close(void)
{
	if (line_handle) { gpiod_line_release(line_handle); line_handle = NULL; }
	if (chip)	{ gpiod_chip_close(chip); chip = NULL; }
}
