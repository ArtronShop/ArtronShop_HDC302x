#include <Arduino.h>
#include <Wire.h>
#include <ArtronShop_HDC302x.h>

ArtronShop_HDC302x hdc302x(&Wire, 0x44); // Address => 0x44

void setup() {
  Serial.begin(115200);

  Wire.begin();
  while (!hdc302x.begin()) {
    Serial.println("HDC302x not found !");
    delay(1000);
  }
}

void loop() {
  if (hdc302x.measure()) {
    Serial.print("Temperature: ");
    Serial.print(hdc302x.temperature(), 1);
    Serial.print(" *C\tHumidity: ");
    Serial.print(hdc302x.humidity(), 1);
    Serial.print(" %RH");
    Serial.println();
  } else {
    Serial.println("HDC302x read error");
  }
  delay(1000);
}
