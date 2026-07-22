#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h> 

RF24 radio(7, 8); 
const byte address[6] = "00001";

struct DataPacket {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
};

DataPacket data;

Servo esc1, esc2, esc3, esc4; 

void setup() {
  Serial.begin(9600);
  
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening(); 

  esc1.attach(3); 
  esc2.attach(5);
  esc3.attach(6); 
  esc4.attach(9); 

  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  
  writeToESCs(1000, 1000, 1000, 1000);
  delay(3000); 
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(DataPacket));
  }

  int baseThrottle = map(data.throttle, 0, 255, 1000, 2000);
  
  if (baseThrottle < 1050) {
    writeToESCs(1000, 1000, 1000, 1000);
  } else {
    
    writeToESCs(baseThrottle, baseThrottle, baseThrottle, baseThrottle);
  }
}

void writeToESCs(int m1, int m2, int m3, int m4) {
  esc1.writeMicroseconds(m1);
  esc2.writeMicroseconds(m2);
  esc3.writeMicroseconds(m3);
  esc4.writeMicroseconds(m4);
}
