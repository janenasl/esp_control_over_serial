#ifndef UTILS_H
#define UTILS_H

#include <ArduinoJson.h>
#include "definitions.h"
#include "Pin.h"
#include "Response.h"

Pin *findPin(Pin list[TOTAL_PINS], int pin);
bool pinExists(Pin list[TOTAL_PINS], int pin);
void executeAction(Pin *pin, DynamicJsonDocument request, Response *res);
int read_dht_sensor(Pin *pin, const char *model, Response *res);
char *errorToString(int rc);

#endif