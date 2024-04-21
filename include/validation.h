#ifndef VALIDATION_H
#define VALIDATION_H

#include <ArduinoJson.h>
#include "definitions.h"
#include "utils.h"

// bool validateRequest(Pin list[TOTAL_PINS], DynamicJsonDocument request);
int validateRequest(Pin list[TOTAL_PINS], DynamicJsonDocument request);
bool validateAction(String action);
bool validatePin(int pin);
bool validateMode(int mode);
bool validateActionArgs(DynamicJsonDocument request);

#endif