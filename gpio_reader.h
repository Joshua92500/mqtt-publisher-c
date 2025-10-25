#ifndef GPIO_READER_H
#define GPIO_READER_H

int gpio_init(int line);

int gpio_read(void);

void gpio_close(void);

#endif
