
#include "Pin.h"

Pin::Pin()

{
	this->pin = -1;
}

Pin::Pin(int pin)
{
	this->pin = pin;
	init();
}

void Pin::init()
{
	setMode(1);
	off();
}

void Pin::setMode(int mode)
{
	if (mode == 1) {
		pinMode(this->pin, OUTPUT);
	} else {
		pinMode(this->pin, INPUT);
	}
}

void Pin::on()
{
	digitalWrite(this->pin, HIGH);
}

void Pin::off()
{
	digitalWrite(this->pin, LOW);
}

int Pin::pinNr()
{
	return this->pin;
}

bool Pin::isOn()
{
	return digitalRead(this->pin) == HIGH ? true : false;
}