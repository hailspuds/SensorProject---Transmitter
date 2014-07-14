#include <VirtualWire.h>
#include "LowPower.h"

#undef round
int lightPin = 0; 
int tempPin = 1; 
int count;
int lastLight;

void setup()
{
    Serial.begin(9600);        // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(3);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);       // Bits per sec
    //get setting for lastLight
    lastLight = analogRead(lightPin);
    randomSeed(analogRead(3));
    count = random(1, 990);
}

void loop()
{
    Serial.println("Start Loop");
    delay(1000);
    int lightPinC1 = analogRead(lightPin);
    int tempPinC1 = analogRead(tempPin);
    char msg[24];
    
    float percentCheck = lastLight * .25;
    
    //If light level has changed by the above percentage, then send via radio. Otherwise, go back to sleep.
    //This is to save power. There's no point transmitting the same thing.
    
    if (lightPinC1 < (lastLight - percentCheck) || lightPinC1 > (lastLight + percentCheck))
    {
      int RadioCount = 0;
      randomSeed(analogRead(3));
      while(RadioCount < 3)
      {
        int randNumber = random(10, 850);
        sprintf(msg, "S:1#L:%i#T:%i#X:XXX#C:%i", lightPinC1,tempPinC1,count);
        Serial.println(msg);
        digitalWrite(13, true);
        vw_send((uint8_t *)msg, strlen(msg));
        vw_wait_tx();
        digitalWrite(13, false);
        RadioCount++;
        Serial.print("Random: ");
        Serial.println(randNumber);
        delay(randNumber);
      }
      
      //Don't let the counter get over 999
      if (count == 999)
      {
        count = 0;
      }  
      count++;
    }

    lastLight = lightPinC1;
    LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, 
                  SPI_OFF, USART0_OFF, TWI_OFF);               
}
