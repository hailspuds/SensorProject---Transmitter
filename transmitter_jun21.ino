#include <VirtualWire.h>

#undef round
int lightPin = 0; 
int tempPin = 1; 
int count = 1;
int lastLight;

void setup()
{
    Serial.begin(9600);        // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(3);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(1200);       // Bits per sec
    //get setting for lastLight
    lastLight = analogRead(lightPin);
    randomSeed(analogRead(3));
    //count = random(1, 990);
}

void loop()
{
    delay(1000);
    int lightPinC1 = analogRead(lightPin);
    int tempPinC1 = analogRead(tempPin);
    char msg[24];
    
    float percentCheck = lastLight * .25;
    
    //If light level has changed by the above percentage, then send via radio. Otherwise, go back to sleep.
    //This is to save power. There's no point transmitting the same thing.
    
    int RadioCount = 0;
    randomSeed(analogRead(3));
    int randNumber = random(1, 19);
    sprintf(msg, "S:1#L:%i#T:%i#R:%i#C:%i", lightPinC1,tempPinC1,randNumber,count);
    Serial.println(msg);
    digitalWrite(13, true);
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx();
    digitalWrite(13, false);
    RadioCount++;
    //Serial.print("Random: ");
    //Serial.println(randNumber);
 
    lastLight = lightPinC1;  
    count++;    
}
