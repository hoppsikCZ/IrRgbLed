#include <Arduino.h>
#include <IRremote.h>
#define IR_RECEIVE_PIN 12
// put function declarations here:
int myFunction(int, int);

void setup() {
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.begin(9600);

}

void loop() {
  if(IrReceiver.decode()){
    unsigned long irData = IrReceiver.decodedIRData.decodedRawData;
    if(irData)
  }
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}