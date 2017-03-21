//
// Created by munk on 3/20/17.
//

#include <stddef.h>

#ifndef ATMEGA2560TEST_ESP8266_H
#define ATMEGA2560TEST_ESP8266_H
#include <stdint.h>


//const char *stdSSID = "testwifi";
//const char *stdPW   = "password";


// Setup to talk on serial 1 port, and connecting to default wifi
void initWiFi();

void testWiFi();

// Function to connect to AP AT+CWJAP="SSID","password"
// Require working uart0!
void connectTo(char *SSID, char *password);

// Function to send Status: 200 to BI

// Function to handle userinput

#endif //ATMEGA2560TEST_ESP8266_H
