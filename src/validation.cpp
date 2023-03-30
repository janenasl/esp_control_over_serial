#include "validation.h"

bool validateRequest(DynamicJsonDocument request)
{
	if (!validateAction(request["action"])) {
		Serial.write("{\"response\": 1, \"msg\": \"Action not valid\"}\r\n");
		return false;
	}
	if (!validatePin((int)request["pin"])) {
		Serial.write("{\"response\": 1, \"msg\": \"Pin is not valid\"}\r\n");
		return false;
	}
	if (request["action"] == ACTION_SET_MODE) {
		if (!validateMode((int)request["mode"])) {
			Serial.write("{\"response\": 1, \"msg\": \"Mode is not valid\"}\r\n");
			return false;
		}
	}
	return true;
}

bool validateAction(String action)
{
	if (action == ACTION_ON || action == ACTION_OFF || action == ACTION_SET_MODE ||
	    action == ACTION_DHT || action == ACTION_GET) {
		return true;
	}
	return false;
}

bool validatePin(int pin)
{
	switch (pin) {
	case D0:
		return true;
		break;
	case D1:
		return true;
		break;
	case D2:
		return true;
		break;
	case D3:
		return true;
		break;
	case D4:
		return true;
		break;
	case D5:
		return true;
		break;
	case D6:
		return true;
		break;
	case D7:
		return true;
		break;
	case D8:
		return true;
		break;
	default:
		return false;
		break;
	}
}

bool validateMode(int mode)
{
	if (mode == (int)OUTPUT || mode == (int)INPUT) {
		return true;
	}
	return false;
}