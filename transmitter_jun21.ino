#include <VirtualWire.h>

int count = 1;
int numbers[10]; // Change 3 to number of integers you wish to send.

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
  numbers[0] = 32767;
  numbers[1] = -2;
  numbers[2] = 0;
  numbers[3] = count;
  numbers[4] = count;
  numbers[5] = count;
  numbers[6] = count;
  numbers[7] = count;
  numbers[8] = count;
  numbers[9] = 9999;
  
  vw_send( (uint8_t *)numbers, sizeof(numbers));
  vw_wait_tx();  // Wait for message to finish
  delay(1000);

  count++;    
}

