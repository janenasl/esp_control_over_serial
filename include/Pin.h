#ifndef PIN_H
#define PIN_H

#include <Arduino.h>

class Pin {
    private:
	int pin;

	void init();

    public:
	Pin();
	Pin(int pin);
	void setMode(int mode);
	void on();
	void off();
	int pinNr();
	bool isOn();
};

#endif