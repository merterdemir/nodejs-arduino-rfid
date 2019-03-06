/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
*/
/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 10
#define RESET_DIO 9
#define DOOR 4
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 
void(* resetFunc) (void) = 0;//declare reset function at address 0
int incomingByte = 0;
void setup()
{ 
  Serial.begin(9600);
  /* Enable the SPI interface */
  pinMode(DOOR, OUTPUT);
  
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
}

void loop()
{
  /* Has a card been detected? */
  if (RC522.isCard())
  {
    /* If so then get its serial number */
    RC522.readCardSerial();
    for(int i=0;i<5;i++)
    {
      Serial.print(RC522.serNum[i], DEC); //to print card detail in Hexa Decimal format
    }
    Serial.print("\n");
    delay(100);
  }
  // send data only when you receive data:
  if (Serial.available() > 0) {
          // read the incoming byte:
          incomingByte = Serial.read();
          delay(100);
          if (incomingByte == 49)
          {
            digitalWrite(DOOR, HIGH);
            delay(750);
            digitalWrite(DOOR, LOW);
          }
          else if (incomingByte == 48)
          {
            digitalWrite(DOOR, LOW);
            delay(200);
          }
  }
}
