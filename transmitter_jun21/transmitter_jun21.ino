#include <VirtualWire.h>

int count = 1;
int numbers[6]; // Change 3 to number of integers you wish to send.
int TemperatureSensorPin = 0;
int LightSensorPin = 1;
int CodeVersion = 2;
int LightStatus = 0;

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
  //Get Temp Readings
  int TemperatureReading = analogRead(TemperatureSensorPin);  
  int LightReading = analogRead(LightSensorPin); 
  
  if (LightReading < 650)
  {
	  //If less than 650, then light - or a light at this point in time - is probably on
	  LightStatus = 1;
  }
  else  //if it's not less than 650 (aka everything else) - the light is likely off.
  {
  	  LightStatus = 0;
  }
  
  // Initialize to some sample values
  numbers[0] = 999;                   //sensorid
  numbers[1] = LightReading;          //light reading
  numbers[2] = TemperatureReading;    //temp reading
  numbers[3] = CodeVersion;           //random 1 - version of the transmitter code
  numbers[4] = 12;                    //random 2 - Transmitter estimation on light status (1 = on, 0 = off)
  numbers[5] = count;                 //count

  vw_send( (uint8_t *)numbers, sizeof(numbers));
  vw_wait_tx();  // Wait for message to finish
  Serial.println("Message sent");
  delay(8000);

  count++;    
}

