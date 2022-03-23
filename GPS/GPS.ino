#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <ClosedCube_HDC1080.h>
#include <Wire.h>

TinyGPS gps;
SoftwareSerial ss(13, 15);
ClosedCube_HDC1080 sensor;

int estado = 0;

static void smartdelay(unsigned long ms);
static void leer_date(TinyGPS &gps);
static void leer_pos(float longitud, float latitud, float altura);
static void leer_date(TinyGPS &gps);
static void leer_sensor();
static void dormir_sensor();

void setup()
{
  Serial.begin(115200);
  ss.begin(9600);
  sensor.begin(0x40);
}

void loop()
{
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  Serial.println();
  gps.f_get_position(&flat, &flon, &age);
  leer_date(gps);
  Serial.println("datos de la posicion");
  leer_pos(flat,flon,gps.f_altitude());
  leer_sensor();
  dormir_sensor();
  smartdelay(1000);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void leer_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("sin fecha valida ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
  }
  smartdelay(0);
}

static void leer_sensor()
{
  double temperatura = sensor.readTemperature();
  double humedad = sensor.readHumidity();
  
  Serial.print("Temperatura = ");
  Serial.print(temperatura);
  Serial.print("ºC  Humedad = ");
  Serial.print(humedad);
  Serial.println("%");
  delay(2000);
  smartdelay(0);
}
static void leer_pos(float longitud, float latitud, float altura)
{
  if (longitud == TinyGPS::GPS_INVALID_F_ANGLE)
  {
      Serial.println('GPS sin posicion calculada');
  }
  else
  {
    Serial.println(' POS = ');
    Serial.print('lon= ');
    Serial.print(longitud);
    Serial.print('lat= ');
    Serial.print('latitud');
    Serial.print('alt= ');
    Serial.print(altura);
    Serial.println(' ');
  }
  smartdelay(0);
}

static void dormir_sensor()
{
  Serial.println("funcion para ir a dormir");
  delay(1000);
  smartdelay(0); 
}
