#include "sensor.hpp"
#include "wirelessLove.hpp"


WirelessLove *wifi;
 
void setup() {
  Serial.begin(9600);      // initialize serial communication
  Serial.print("hi there");
  initCounter();
  pinMode(6,INPUT); 
  pinMode(7,INPUT); 
  attachInterrupt(6, rising_IRQ_S1, RISING); 
  attachInterrupt(7, falling_IRQ_S1, FALLING); 

  IPAddress broadcastIP(192,168,0,255);
  wifi = new WirelessLove("roboy","wiihackroboy", broadcastIP); 
  wifi->initUDPSockets();
}

void loop() {
  Sweep * detectedSweep = FIFO128_read(sweepFIFO); 
  while( NULL != detectedSweep){
      Serial.print("sweepDuration ");
      Serial.print(detectedSweep->sweepDuration);
      Serial.print(" lighthouse ");
      Serial.print(detectedSweep->lighthouse);
      Serial.print(" rotor ");
      Serial.println(detectedSweep->rotor);
      wifi->broadcast_send((uint8_t*)detectedSweep, sizeof(Sweep));
      free(detectedSweep); 
      detectedSweep = FIFO128_read(sweepFIFO); 
  }
}
