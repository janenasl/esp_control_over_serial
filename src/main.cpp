#include <Arduino.h>
#include <ArduinoJson.h>
#include "definitions.h"
#include "validation.h"
#include "DHT.h"

#define DHTTYPE DHT11 // DHT 11

void executeAction(DynamicJsonDocument request);
void turnOnPin(int pin);
void turnOffPin(int pin);
void setPinMode(int pin, int mode);
void readPinData(int pin);

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

void turnOnPin(int pin)
{
	digitalWrite(pin, HIGH);
}

void turnOffPin(int pin)
{
	digitalWrite(pin, LOW);
}

void setPinMode(int pin, int mode)
{
	pinMode(pin, mode);
}

void getPinValue(int pin, char *buffer)
{
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint32_t *reg = portModeRegister(port);

	if (*reg & bit)
	{
		sprintf(buffer, "{\"response\":1,\"msg\": \"Pin mode is output\"}\r\n");
		return;
	}

	sprintf(buffer, "{\"response\":0,\"value\":%d\r\n", digitalRead(pin));
}

void readDHTData(int pin, char *buffer)
{
	DHT dht(pin, DHTTYPE);
	dht.begin();

	float h = dht.readHumidity();
	float t = dht.readTemperature();

	if (isnan(h) || isnan(t))
	{
		sprintf(buffer, "{\"response\": 1, \"msg\": \"Failed to read from DHT sensor!\"}\r\n");
		return;
	}

	// Compute heat index in Celsius (isFahreheit = false)
	float hic = dht.computeHeatIndex(t, h, false);
	sprintf(buffer, "{\"response\":0,\"dht\":{\"humidity\":%.2f,\"temperature\":%.2f,\"heat_index\":%.2f}}\r\n", h, t, hic);
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
		char buffer[50];
		getPinValue(request["pin"], (char *)&buffer);
		Serial.write(buffer);
	}
	else if (request["action"] == ACTION_DHT)
	{
		char buffer[100];
		readDHTData(request["pin"], (char *)&buffer);
		Serial.write(buffer);
	}
}
