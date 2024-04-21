#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

#include <Arduino.h>
#include <dhtnew.h>
#include "Pin.h"

class DHT_Sensor {
    private:
	Pin *pin       = nullptr;
	DHTNEW *sensor = nullptr;

	bool check(int rc);

    public:
	DHT_Sensor(Pin *pin);
	DHT_Sensor(Pin *pin, int type);
	float *getData();
};

#endif
