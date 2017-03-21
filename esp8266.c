//
// Created by munk on 3/20/17.
//

#include <avr/interrupt.h>
#include "esp8266.h"
#include "uart_int.h"

// Serial setup
//#define BAUD        9600
//#define DATABIT     8
//#define PARITY      'N'
//#define RX_Int      1
//#define SERIAL_PORT 1;

/*ISR(USART1_RX_vect){
    // Send the response to the serial0 monitor
//    SendString("Got rx interrupt\r\n", 0);
    char recv[3];
    recv[0] = ReadChar(1);
//    recv[1] = '\r';
//    recv[2] = '\n';
    SendChar(recv[0], 0);
}*/

void initWiFi(){
    // Setup the serial connection
    InitUART(115200, 8, 'N', 0, 1);
    SendString("Created uart\r\n", 0);
    // Test AT
    testWiFi();

    // Connect to wifi
    //connectTo(stdSSID, stdPW);

}

void testWiFi() {
    // Write test AT command
    char AT_test[] = "AT";
    SendString("A\r\n", 0);
    SendChar('A', 1);
    SendChar('T', 1);
    SendString("T\r\n", 0);
    SendChar('\r', 1);
    SendString("\\r\r\n", 0);
    SendChar('\n', 1);
    SendString("\\n\r\n", 0);

//    while(CharReady(1) == 0);
    SendString("Done waiting\r\n", 0);
//    while(CharReady(1) != 0){
        SendChar(ReadChar(1), 0);
//    }

}


void connectTo(char *SSID, char *password) {

}