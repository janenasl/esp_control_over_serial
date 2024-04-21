#include "Response.h"

void Response::sendResponse()
{
	StaticJsonDocument<250> doc;
	char json[256];
	doc["rc"]  = this->rc;
	doc["msg"] = this->message;
	if (this->length > 0) {
		doc.createNestedObject("data");
		for (int i = 0; i < this->length; i++) {
			doc["data"][this->labels[i]] = this->data[i];
		}
	}
	serializeJson(doc, json);
	strcat(json, "\r\n");
	Serial.write(json);
}

int Response::find(char *label)
{
	int index = -1;
	for (int i = 0; i < this->length; i++) {
		if (strcmp(this->labels[i], label) == 0) {
			index = i;
			break;
		}
	}
	return index;
}

void Response::addData(char *label, float value)
{
	int index = find(label);
	if (index > -1) {
		this->data[index] = value;
	} else {
		Serial.println(label);
		strcpy(this->labels[length], label);
		this->data[length] = value;
		length++;
	}
}

void Response::setRc(int rc)
{
	this->rc = rc;
}

void Response::setMessage(char *msg)
{
	strcpy(this->message, msg);
}