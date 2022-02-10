#include <ClosedCube_HDC1080.h>
#include <Wire.h>

ClosedCube_HDC1080 sensor;

void setup(){
sensor.begin(0x40);
Serial.begin(9600);
}

void loop(){
  double temperature = sensor.readTemperature();
  double humedad = sensor.readHumidity();

  for(int i =0;i<=20;i++){
    temperature = temperature+ sensor.readTemperature();
    humedad=humedad+sensor.readHumidity();
  }

  Serial.println("Temperatura = ");
  Serial.println(temperature);
  Serial.println("°C Humedad = ");
  Serial.println(humedad);
  Serial.println("%");
  delay(2000);
}
