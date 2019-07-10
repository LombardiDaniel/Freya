#include <DallasTemperature.h>
#include <OneWire.h>

/*Variables*/
const int pin_temp = 2;
const int pin_humi;

float temp;
long humi;

/*Objects*/
OneWire oneWire(pin_temp);
DallasTemperature term(&oneWire);

void setup() {

  Serial.begin(9600);
  pinMode(pin_humi, INPUT);

  term.begin(); //isso aqui é do dallas temp

}

void loop() {

  term.requestTemperatures();

  temp = term.getTempCByIndex(0);

  Serial.print(temp);
  Serial.println(" ºC");

  for (int i = 0; i < 100; i++) {
    humi += analogRead(pin_humi);
    delay(5);
  }
  humi = humi/100;

  humi = (- (humi)/6.71 + 100)*2;

  if (humi > 100) {
    humi = 100;
  } else if (humi < 0) {
    humi = 0;
  }

  Serial.print(humi);
  Serial.print("%       ");

  delay(100);

}
