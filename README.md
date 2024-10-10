# ArtronShop_HDC302x

Arduino library of HDC302x Digital humidity and temperature sensor

## Examples

```C++
#include <Arduino.h>
#include <Wire.h>
#include <ArtronShop_HDC302x.h>

ArtronShop_HDC302x HDC302x(&Wire, 0x44); // HDC302x => 0x44

void setup() {
  Serial.begin(115200);

  Wire.begin();
  while (!HDC302x.begin()) {
    Serial.println("HDC302x not found !");
    delay(1000);
  }
}

void loop() {
  if (HDC302x.measure()) {
    Serial.print("Temperature: ");
    Serial.print(HDC302x.temperature(), 1);
    Serial.print(" *C\tHumidity: ");
    Serial.print(HDC302x.humidity(), 1);
    Serial.print(" %RH");
    Serial.println();
  } else {
    Serial.println("HDC302x read error");
  }
  delay(1000);
}
```

