#ifndef VALIDATION_H
#define VALIDATION_H

#include <ArduinoJson.h>
#include "definitions.h"

bool validateRequest(DynamicJsonDocument request);
bool validateAction(String action);
bool validatePin(int pin);
bool validateMode(int mode);

#endif