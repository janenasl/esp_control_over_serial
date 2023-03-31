#include <Arduino.h>
#include <ArduinoJson.h>
#include "definitions.h"
#include "validation.h"
#include "action_handler.h"


void executeAction(DynamicJsonDocument request);

void setup()
{
	Serial.begin(9600);
	pinMode(D0, OUTPUT);
	pinMode(D1, OUTPUT);
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinMode(D7, OUTPUT);
	pinMode(D8, OUTPUT);
}

void loop()
{
	String incomingString = "";
	DynamicJsonDocument request(1024);
	if (Serial.available() > 0)
	{
		incomingString = Serial.readString();
		deserializeJson(request, incomingString);
		if (!validateRequest(request))
		{
			// Serial.println("Failed");
			return;
		}
		// Serial.println("Success");
		executeAction(request);
	}
}

void executeAction(DynamicJsonDocument request)
{
	if (request["action"] == ACTION_ON)
	{
		turnOnPin((int)request["pin"]);
		Serial.write("{\"response\": 0, \"msg\": \"Pin was turned on\"}\r\n");
	}
	else if (request["action"] == ACTION_OFF)
	{
		turnOffPin((int)request["pin"]);
		Serial.write("{\"response\": 0, \"msg\": \"Pin was turned off\"}\r\n");
	}
	else if (request["action"] == ACTION_SET_MODE)
	{
		setPinMode(request["pin"], request["mode"]);
		Serial.write("{\"response\": 0, \"msg\": \"Pin mode was changed\"}\r\n");
	}
	else if (request["action"] == ACTION_GET)
	{
		char respinse[50];
		getPinValue(request["pin"], (char *)&respinse);
		Serial.write(respinse);
	}
	else if (request["action"] == ACTION_READ)
	{
		char respinse[100];
		readInput(request, (char *)&respinse);
		Serial.write(respinse);
	}
}
