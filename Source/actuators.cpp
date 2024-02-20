/*
Controls outputs from the thing for lights and heating
*/
#include "config.h"
#include "actuators.h"
#include "display.h"
#include "mbed.h"

//extern struct MyData myD;

extern struct myData{
     float tempC;
     float tempSet; // default thermostat setting
     int heaterState; // 0 for off 1 for on
     float lightL;
     float lightSet; // default ambient light level setting
     int lightState; // 0 lights are off 1 for lights illuminated
 } myD;

void doActuations()
{
    DigitalOut lightState(LIGHT_LED);
    DigitalOut heaterState(HEATER_LED);

    while(true)
    {
        if (myD.lightL < myD.lightSet - DEAD_BAND_L)
            {
              myD.lightState = true;
              lightState = 1;
            }
        else if (myD.lightL < myD.lightSet + DEAD_BAND_L)
            {
              myD.lightState = false;
              lightState = 0;
            }   
        if (myD.tempC < myD.tempSet - DEAD_BAND_T)
            {
              myD.heaterState = true;
              heaterState = 1;
            }
        else if (myD.tempC < myD.tempSet + DEAD_BAND_T)
            {
              myD.heaterState = false;
              heaterState = 0;
            }  
            sprintf(myMessage, " %s " , myD.heaterState?"ON":"OFF");
            
            ThisThread::sleep_for(100); 
    }
}
