# ESP8266 over serial
This is a small project which allows you to control ESP8266 pins over the serial.

It excepts JSON messages for controlling it and it's baud rate is set to **9600**.

Only 9 pins are usable at the moment.

By default all pins are setted to **OUTPUT** mode.

## Actions
At this time it allows just 4 actions, but only 3 actions are working:
* on
* off
* set_mode
* get

### on
This action is used to set the digital pin to **HIGH**.

To use this command you need to send a JSON formatted like this:
```{"action": "on", "pin": 12} ```

### off
This action is used to set the digital pin to **LOW**.

To use this command you need to send a JSON formatted like this:
```{"action": "off", "pin": 12} ```

### set_mode
This action is used to set the digital pin's working mode. It can be **0** or **1**. **0** stands for **INPUT** and **1** stands for **OUTPUT**.

To use this command you need to send a JSON formatted like this:
```{"action": "set_mode", "pin": 12, "mode": 1} ```

### get
This command isn't implemented at the moment. It purpose will be to read the digital pin's or ADC value. 

## Supported pins
At this moment only 9 digital pins are supported:
* **D0** - gpio16
* **D1** - gpio5
* **D2** - gpio4
* **D3** - gpio0
* **D4** - gpio2
* **D5** - gpio14
* **D6** - gpio12
* **D7** - gpio13
* **D8** - gpio15

## Reading serial from Linux

To read from and send data to serial port using ```cat```, first you need to configure the serial port to not echo back the result.

Execute this command to turn of echo mode for serial port ```stty 9600 -F /dev/ttyUSB0 raw -echo```
