/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <wwVL53L0X.h>

wwVL53L0X irDist(&Wire1);        // Choose your SPI line: 'Wire' or Wire1

#define SerialComputer SerialUSB // use 'Serial' instead of 'SerialUSB' on an ordinary Arduino

void setup()
{
   SerialComputer.begin(115200);
   while(!SerialComputer)        // necessary for Arduino DUE/Frankenstein-DUE to wait for the serial connection
   ;
   SerialComputer.println("Hello Computer");
   
   Wire1.begin();              // Choose your SPI line: 'Wire' or Wire1

   irDist.init();
   irDist.setTimeout(500);

   // Start continuous back-to-back mode (take readings as
   // fast as possible).  To use continuous timed mode
   // instead, provide a desired inter-measurement period in
   // ms (e.g. sensor.startContinuous(100)).
   irDist.startContinuous();
}

void loop()
{
   int distance;

   
   distance = irDist.readRangeContinuousMillimeters();
   
   if (distance <2000){
      SerialComputer.println();
      SerialComputer.print(distance);
   }
   else {
      SerialComputer.print(".");
   }
   if (irDist.timeoutOccurred()) { SerialComputer.println(" TIMEOUT"); }
}
