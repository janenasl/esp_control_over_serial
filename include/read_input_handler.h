#ifndef __READ_INPUT_HANDLER_H
#define __READ_INPUT_HANDLER_H
#include <ArduinoJson.h>

struct ReadInput_Command_Args
{
    DynamicJsonDocument *request;
    char *response_buffer;
};

struct ReadInput_Command
{
    String name;
    bool (*function_pointer)(struct ReadInput_Command_Args *);
};

enum
{
    READ_INPUT_DHT,
    __READ_INPUT_LAST
};

extern const struct ReadInput_Command read_input_handler_command_lut[];

#endif //__READ_INPUT_HANDLER_H