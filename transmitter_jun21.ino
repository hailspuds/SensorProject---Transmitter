#include <VirtualWire.h>

int count = 1;
int numbers[6]; // Change 3 to number of integers you wish to send.

void setup()
{
  Serial.begin(9600);
  Serial.println("Setting up Transmitter");

  vw_set_tx_pin(3);
  vw_set_ptt_inverted(true);
  vw_setup(1200); // Bits per sec  
}

void loop()
{
  // Initialize to some sample values
  numbers[0] = 999;     //sensorid
  numbers[1] = 123;   //light reading
  numbers[2] = 456;   //temp reading
  numbers[3] = 789;   //random 1
  numbers[4] = 12;   //random 2
  numbers[5] = count; //count

  vw_send( (uint8_t *)numbers, sizeof(numbers));
  vw_wait_tx();  // Wait for message to finish
  Serial.println("Message sent");
  delay(8000);

  count++;    
}

