#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <mosquitto.h>
#include "gpio_reader.h"


#define MQTT_HOST "10.0.0.142"
#define MQTT_PORT 1883
#define MQTT_TOPIC "test/topic"
#define GPIO_LINE 23

static volatile int keep_running = 1;

void handle_sigint(int sig)
{
	(void)sig;
	keep_running = 0;
}

int main(int argc, char **argv)
{
	signal(SIGINT, handle_sigint);

	const char *prefix = (argc > 1) ? argv[1] : "GPIO23";

	// Init GPIO
	if (gpio_init(GPIO_LINE) != 0) {
		fprintf(stderr, "failed to init GPIO %d\n", GPIO_LINE);
		return 1;
	}

	// Init MQTT

	mosquitto_lib_init();

	struct mosquitto *mq = mosquitto_new("pi-publisher", true, NULL);
	if (!mq) { 
		fprintf(stderr, "mosquitto_new failed\n"); 
		gpio_close(); 
		return 1; 
	}

	int rc = mosquitto_connect(mq, MQTT_HOST, MQTT_PORT, 60);
	if (rc != MOSQ_ERR_SUCCESS) {
		fprintf(stderr, "connect failed: %s\n", mosquitto_strerror(rc));
		mosquitto_destroy(mq);
		mosquitto_lib_cleanup();
		gpio_close();
		return 1;
	}

	// MQTT loop
	while (keep_running) {
		int v = gpio_read();
		if (v < 0) {
			fprintf(stderr, "gpio_read error\n");
			break;
		}

		const char *state = v ? "hi" : "lo";
		const char *color = v ? "red" : "yellow";

		char payload[128];
		snprintf(payload, sizeof(payload), "GPIO23: %s, %s", state, color);

		rc = mosquitto_publish(mq, NULL, MQTT_TOPIC, strlen(payload), payload, 0, false);

		if (rc != MOSQ_ERR_SUCCESS) {
			fprintf(stderr, "publish failed: %s\n", mosquitto_strerror(rc));
		} else {
		printf("Sent %s\n", payload);
		}

		usleep(500000);
	}

	mosquitto_disconnect(mq);
	mosquitto_destroy(mq);
	mosquitto_lib_cleanup();
	gpio_close();
	printf("Cleanup completed\n");
	return 0;
}
