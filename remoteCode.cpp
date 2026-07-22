#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); 
const byte address[6] = "00001";

struct DataPacket {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
};

DataPacket data;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH); 
  radio.stopListening(); 
  
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
}

void loop() {
  data.throttle = map(analogRead(A0), 0, 1023, 0, 255);
  data.yaw      = map(analogRead(A1), 0, 1023, 0, 255);
  data.pitch    = map(analogRead(A2), 0, 1023, 0, 255);
  data.roll     = map(analogRead(A3), 0, 1023, 0, 255);

  radio.write(&data, sizeof(DataPacket));
  
  delay(20); 
}
