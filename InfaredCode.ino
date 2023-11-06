#include <LiquidCrystal.h>
#include <IRremote.h>

LiquidCrystal display(9, 8, 7, 6, 5, 4);
IRsend irsend;

bool decodeIRcheck = true;

void setup()
{
  Serial.begin(9600);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  IrReceiver.begin(2);
  display.begin(16,2);
  display.clear();
  display.setCursor(0,0);
  display.print("Ready 4 IR!");
}

void loop() {
  if (digitalRead(13) == LOW) {
      display.setCursor(14,1);
      display.print("=>");
      decodeIRcheck = false;
      Serial.println("start IRSEND");
      IrSender.sendNEC(0x5583, 0x99, 100);
      Serial.println("stop IRSEND");
  } 
  if (digitalRead(13) == HIGH) {
    decodeIRcheck = true;
    display.setCursor(14,1);
    display.print("  ");
  }
  if (digitalRead(12) == LOW) {
      String LockedCode = String({IrReceiver.decodedIRData.decodedRawData}, HEX);
      display.setCursor(0,1);
      display.print("LOCK:" + LockedCode);
  }
  if (decodeIRcheck == true) {
    if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      display.setCursor(0,0);
      display.print("CODE:" + String(IrReceiver.decodedIRData.decodedRawData, HEX));
      IrReceiver.printIRResultShort(&Serial);
      IrReceiver.printIRSendUsage(&Serial);
      IrReceiver.resume();
    }
  }
}
