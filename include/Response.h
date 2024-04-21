#ifndef RESPONSE_H
#define RESPONSE_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "definitions.h"

class Response {
    private:
	int rc	   = 0;
	int length = 0;
	char labels[10][20];
	float data[10];
	char message[128];

    public:
	void sendResponse();
	void addData(char *label, float value);
	void setRc(int rc);
	int find(char *label);
	void setMessage(char *msg);
};
#endif