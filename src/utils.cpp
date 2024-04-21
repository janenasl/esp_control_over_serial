#include "utils.h"
#include "Dht_sensor.h"

Pin *findPin(Pin list[TOTAL_PINS], int pinNr)
{
	Pin *pin = nullptr;
	for (int i = 0; i < TOTAL_PINS; ++i) {
		if (list[i].pinNr() == pinNr) {
			pin = &list[i];
			break;
		}
	}
	return pin;
}

bool pinExists(Pin list[TOTAL_PINS], int pin)
{
	bool exists = false;
	for (int i = 0; i < TOTAL_PINS; ++i) {
		if (list[i].pinNr() == pin) {
			exists = true;
			break;
		}
	}
	return exists;
}

void executeAction(Pin *pin, DynamicJsonDocument request, Response *res)
{
	res->setRc(SUCCESS);
	if (request["action"] == ACTION_ON) {
		pin->on();
		res->setMessage("Pin was turned on");
	} else if (request["action"] == ACTION_OFF) {
		pin->off();
		res->setMessage("Pin was turned off");
	} else if (request["action"] == ACTION_SET_MODE) {
		pin->setMode((int)request["mode"]);
		res->setMessage("Pin mode was changed");
	} else if (request["action"] == ACTION_GET) {
		if (request["sensor"] == "dht") {
			int rc = read_dht_sensor(pin, request["model"].as<const char *>(), res);
			res->setRc(rc);
		}
	}
}

int read_dht_sensor(Pin *pin, const char *model, Response *res)
{
	DHT_Sensor *dht = nullptr;
	float *data	= nullptr;
	int dht_type	= strcmp(model, "dht11") == 0 ? 11 : strcmp(model, "dht22") == 0 ? 22 : 0;
	if (dht_type == 0) {
		res->setMessage("DHT type is not supported");
		return SENSOR_NOT_SUPPORTED;
	}
	dht  = new DHT_Sensor(pin, dht_type);
	data = dht->getData();
	if (data == nullptr) {
		res->setMessage("DHT returned no data");
	} else {
		res->setMessage("DHT data successfully read");
		res->addData("humidity", data[0]);
		res->addData("temperature", data[1]);
		delete[] data;
	}
	delete dht;
	return SUCCESS;
}

char *errorToString(int rc)
{
	char *msg = new char[128];
	switch (rc) {
	case ACTION_NOT_VALID:
		strcpy(msg, "Action is not valid");
		break;
	case PIN_NOT_VALID:
		strcpy(msg, "Pin is not valid");
		break;
	case MODE_NOT_VALID:
		strcpy(msg, "Mode is not valid");
		break;
	case SENSOR_NOT_SUPPORTED:
		strcpy(msg, "Sensor is not supported");
		break;
	case SENSOR_RETURNED_NO_DATA:
		strcpy(msg, "Sensor didn't returned any data");
		break;
	case MISSING_ARGUMENTS:
		strcpy(msg, "Request is missing required arguments");
		break;
	default:
		strcpy(msg, "");
		break;
	}
	return msg;
}
