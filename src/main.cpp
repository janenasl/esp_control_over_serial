#include <Arduino.h>
#include <ArduinoJson.h>

//available pins
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15

//available actions
#define ACTION_ON	"on"
#define ACTION_OFF	"off"
#define ACTION_SET_MODE "set_mode"
#define ACTION_GET	"get"

bool validatePin(int pin);
bool validateMode(int mode);
bool validateAction(String action);
bool validateRequest(DynamicJsonDocument request);
void executeAction(DynamicJsonDocument request);
void turnOnPin(int pin);
void turnOffPin(int pin);
void setPinMode(int pin, int mode);

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
	if (Serial.available() > 0) {
		incomingString = Serial.readString();
		deserializeJson(request, incomingString);
		if (!validateRequest(request)) {
			// Serial.println("Failed");
			return;
		}
		// Serial.println("Success");
		executeAction(request);
	}
}

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
	    action == ACTION_GET) {
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

void executeAction(DynamicJsonDocument request)
{
	if (request["action"] == ACTION_ON) {
		turnOnPin((int)request["pin"]);
		Serial.write("{\"response\": 0, \"msg\": \"Pin was turned on\"}\r\n");
	} else if (request["action"] == ACTION_OFF) {
		turnOffPin((int)request["pin"]);
		Serial.write("{\"response\": 0, \"msg\": \"Pin was turned off\"}\r\n");
	} else if (request["action"] == ACTION_SET_MODE) {
		setPinMode(request["pin"], request["mode"]);
		Serial.write("{\"response\": 0, \"msg\": \"Pin mode was changed\"}\r\n");
	} else if (request["action"] == ACTION_SET_MODE) {
		//coming soon
	}
}
