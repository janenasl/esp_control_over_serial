#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//available actions
#define ACTION_ON	"on"
#define ACTION_OFF	"off"
#define ACTION_SET_MODE "set_mode"
#define ACTION_GET	"get"
#define TOTAL_PINS	9

// enum ACTIONS {
// 	ACTION_ON = 1,
// 	ACTION_OFF,
// 	ACTION_SET_MODE,
// 	ACTION_GET
// }

//available pins
enum PINS {
	PIN_D0 = 16,
	PIN_D1 = 5,
	PIN_D2 = 4,
	PIN_D3 = 0,
	PIN_D4 = 2,
	PIN_D5 = 14,
	PIN_D6 = 12,
	PIN_D7 = 13,
	PIN_D8 = 15
};

const int pinList[] = { PIN_D0, PIN_D1, PIN_D2, PIN_D3, PIN_D4, PIN_D5, PIN_D6, PIN_D7, PIN_D8 };

enum OPERATIONS {
	SUCCESS		 = 0,
	ACTION_NOT_VALID = 101,
	PIN_NOT_VALID,
	MODE_NOT_VALID,
	SENSOR_NOT_SUPPORTED,
	SENSOR_RETURNED_NO_DATA,
	MISSING_ARGUMENTS
};

#endif