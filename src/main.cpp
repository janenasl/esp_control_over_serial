#include <Arduino.h>
#include <ArduinoJson.h>
#include "Pin.h"
#include "Response.h"
#include "definitions.h"
#include "validation.h"
#include "utils.h"

Pin pins[TOTAL_PINS];

void setup()
{
	Serial.begin(9600);
	for (int i = 0; i < TOTAL_PINS; ++i) {
		pins[i] = Pin(pinList[i]);
	}
}

void loop()
{
	int rc	      = 0;
	Response *res = new Response();
	DynamicJsonDocument request(512);
	if (Serial.available() > 0) {
		deserializeJson(request, Serial.readString());
		rc = validateRequest(pins, request);
		if (!rc) {
			executeAction(findPin(pins, (int)request["pin"]), request, res);
		} else {
			res->setRc(rc);
			res->setMessage(errorToString(rc));
		}
		res->sendResponse();
	}
	delete res;
}
