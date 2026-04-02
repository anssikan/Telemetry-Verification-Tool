#include "DHT.h"

DHT dht(2, DHT22);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.print(F("humidity: "));
  Serial.print(humidity);
  Serial.print(F("%,  temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C\n"));
}