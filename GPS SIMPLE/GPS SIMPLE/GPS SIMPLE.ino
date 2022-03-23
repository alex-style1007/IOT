#include <SoftwareSerial.h>
static const int RXPin = 2, TXPin = 0;
static const uint32_t GPSBaud = 9600;
// The serial connection to the GPS device
SoftwareSerial ss(TXPin,RXPin);
void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.println("iniciando el programa");
}
void loop()
{
  // Output raw GPS data to the serial monitor
//  Serial.println("entrando al modo del GPS");
  while (ss.available() > 0){
    Serial.write(ss.read());
  }
}
