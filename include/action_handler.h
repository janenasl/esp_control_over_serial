#ifndef __ACTION_HANDLER_H
#define __ACTION_HANDLER_H

void turnOnPin(int pin);
void turnOffPin(int pin);
void setPinMode(int pin, int mode);
void getPinValue(int pin, char *response);
void readInput(DynamicJsonDocument request, char *response);


#endif //__ACTION_HANDLER_H