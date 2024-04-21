#include "Dht_sensor.h"

DHT_Sensor::DHT_Sensor(Pin *pin)
{
	this->pin    = pin;
	this->sensor = new DHTNEW(this->pin->pinNr());
	this->sensor->setType(11);
	this->sensor->setHumOffset(10);
	this->sensor->setTempOffset(-3.5);
}

//supports these types: 11, 22, 23
DHT_Sensor::DHT_Sensor(Pin *pin, int type)
{
	this->pin    = pin;
	this->sensor = new DHTNEW(this->pin->pinNr());
	this->sensor->setType(type);
	this->sensor->setHumOffset(8);
	this->sensor->setTempOffset(-2);
}

float *DHT_Sensor::getData()
{
	float *data = new float[2];
	int rc	    = this->sensor->read();
	if (check(rc)) {
		return nullptr;
	}
	data[0] = this->sensor->getHumidity();
	data[1] = this->sensor->getTemperature();
	return data;
}

bool DHT_Sensor::check(int rc)
{
	bool errors = false;
	switch (rc) {
	case DHTLIB_ERROR_CHECKSUM:
		errors = true;
		break;
	case DHTLIB_ERROR_TIMEOUT_A:
		errors = true;
		break;
	case DHTLIB_ERROR_TIMEOUT_B:
		errors = true;
		break;
	case DHTLIB_ERROR_TIMEOUT_C:
		errors = true;
		break;
	case DHTLIB_ERROR_TIMEOUT_D:
		errors = true;
		break;
	case DHTLIB_ERROR_SENSOR_NOT_READY:
		errors = true;
		break;
	case DHTLIB_ERROR_BIT_SHIFT:
		errors = true;
		break;
	case DHTLIB_WAITING_FOR_READ:
		errors = true;
		break;
	default:
		break;
	}
	return errors;
}
