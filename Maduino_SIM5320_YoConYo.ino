
// Librerias para crear nuevo Serial (Serial2)
#include <Arduino.h>   // required before wiring_private.h
#include "wiring_private.h" // pinPeripheral() function

// Configuramos: D10 --> TX y D11 -->> RX
Uart Serial2 (&sercom1, 11, 10, SERCOM_RX_PAD_0, UART_TX_PAD_2);
void SERCOM1_Handler()
{
  Serial2.IrqHandler();
}

void setup() {
  SerialUSB.begin(115200);
  
  Serial2.begin(115200);
  pinPeripheral(10, PIO_SERCOM);
  pinPeripheral(11, PIO_SERCOM);
}

void loop() {
  if (SerialUSB.available()) {      // If anything comes in Serial (USB),
    Serial2.write(SerialUSB.read());   // read it and send it out Serial1 (pins 0 & 1)
  }

  if (Serial2.available()) {     // If anything comes in Serial1 (pins 0 & 1)
    SerialUSB.write(Serial2.read());   // read it and send it out Serial (USB)
  }
}
