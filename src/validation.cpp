#include "validation.h"

int validateRequest(Pin list[TOTAL_PINS], DynamicJsonDocument request)
{
	if (!validateAction(request["action"])) {
		return ACTION_NOT_VALID;
	}
	if (!validateActionArgs(request)) {
		return MISSING_ARGUMENTS;
	}
	if (!pinExists(list, (int)request["pin"])) {
		return PIN_NOT_VALID;
	}
	if (request["action"] == ACTION_SET_MODE) {
		if (!validateMode((int)request["mode"])) {
			return MODE_NOT_VALID;
		}
	}
	return SUCCESS;
}

bool validateActionArgs(DynamicJsonDocument request)
{
	if (request["action"] == ACTION_ON || request["action"] == ACTION_OFF) {
		if (!request.containsKey("pin")) {
			return false;
		}
	}
	if (request["action"] == ACTION_SET_MODE) {
		if (!request.containsKey("pin") || !request.containsKey("mode")) {
			return false;
		}
	}
	if (request["action"] == ACTION_GET) {
		if (!request.containsKey("pin") || !request.containsKey("sensor") ||
		    !request.containsKey("model")) {
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

bool validateMode(int mode)
{
	if (mode == (int)OUTPUT || mode == (int)INPUT) {
		return true;
	}
	return false;
}