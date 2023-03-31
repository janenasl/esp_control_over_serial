#include "DHT.h"
#include <ArduinoJson.h>
#include "read_input_handler.h"

void turnOnPin(int pin)
{
    digitalWrite(pin, HIGH);
}

void turnOffPin(int pin)
{
    digitalWrite(pin, LOW);
}

void setPinMode(int pin, int mode)
{
    pinMode(pin, mode);
}

void getPinValue(int pin, char *response)
{
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint32_t *reg = portModeRegister(port);

    if (*reg & bit)
    {
        sprintf(response, "{\"response\":1,\"msg\": \"Pin mode is output\"}\r\n");
        return;
    }

    sprintf(response, "{\"response\":0,\"value\":%d\r\n", digitalRead(pin));
}

void readInput(DynamicJsonDocument request, char *response)
{
    ReadInput_Command_Args handler_args;
    int command_id = 0;
    bool is_valid = false;
    for (uint8_t command = 0; command < __READ_INPUT_LAST; command++)
    {

        if (read_input_handler_command_lut[command].name.compareTo(request["action"]))
        {

            handler_args.request = &request;
            handler_args.response_buffer = response;
            is_valid = true;

            break;
        }
    }
    if (is_valid)
    {
        Serial.write("action2");
        read_input_handler_command_lut[command_id].function_pointer(&handler_args);
    }
}