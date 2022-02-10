
#include <Wire.h>
#include <AP3216_WE.h>

AP3216_WE myAP3216 = AP3216_WE();

void setup() {
  Serial.begin(9600);
  Wire.begin();
	myAP3216.init();

  myAP3216.setMode(AP3216_ALS); // Uncomment and adjust if needed 
  
  myAP3216.setLuxRange(RANGE_20661);
 
  delay(1000); // without delay the first values will be zero
}

void loop() {
  
  float als = myAP3216.getAmbientLight();
  Serial.print("Lux: "); Serial.println(als);
  delay(1000);
}
