#include "read_input_handler.h"
#include "DHT.h"
#include <ArduinoJson.h>

#define DHTTYPE DHT11 // DHT 11

bool read_input_handler_dht(ReadInput_Command_Args *args);

const struct ReadInput_Command read_input_handler_command_lut[] = {
    [READ_INPUT_DHT] = {
        .name = "dht",
        .function_pointer = &read_input_handler_dht,
    }};

bool read_input_handler_dht(ReadInput_Command_Args *args)
{
		// Serial.write("handler");

    DynamicJsonDocument data = *args->request;
     
    DHT dht(data["pin"], DHTTYPE);
	dht.begin();

	float h = dht.readHumidity();
	float t = dht.readTemperature();

	if (isnan(h) || isnan(t))
	{
		sprintf(args->response_buffer, "{\"response\": 1, \"msg\": \"Failed to read from DHT sensor!\"}\r\n");
		return -1;
	}

	// Compute heat index in Celsius (isFahreheit = false)
	float hic = dht.computeHeatIndex(t, h, false);
	sprintf(args->response_buffer, "{\"response\":0,\"dht\":{\"humidity\":%.2f,\"temperature\":%.2f,\"heat_index\":%.2f}}\r\n", h, t, hic);
    return 0;
}
