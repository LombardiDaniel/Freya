/**
 * @Author: DanielLombardi
 * @Date:   2019-07-10T21:15:37-03:00
 * @Last modified by:   DanielLombardi
 * @Last modified time: 2019-07-23T16:51:01-03:00

Needs Fixing:
  linha 84~90 fazer com testes
  linha 145~152 (luz)- descobrir o valor máximo que da pra ter
    e usar a função map(value, fromLow, fromHigh, toLow, toHigh);

 */

#include <DallasTemperature.h>
#include <OneWire.h>
#include <DS3231.h>
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

/*Pins*/
#define pin_temp 2
#define pin_moist //analog
#define pin_light_sensor //analog
#define pin_hose //digital
#define pinCS //analog
#define pin_reset //analog
#define pin_relay //digital
#define pin_servo //PWM

/*Variables*/
const int steps = 2038;
const float rot_speed = 9;
const int min_moist; // valor de 0-100 (%)
const int max_moint; //valor para medir qnd tenq parar
const int min_temp; // medir qnd tenq começar
float X;
str hatch_state;

/*Objects*/
File myFile;
OneWire oneWire(pin_temp);
DallasTemperature term(&oneWire);
Servo hatch; //pinos do stepper
Time t;
DS3231 rtc(SDA, SCL);

void setup() {

  pinMode(pin_temp, INPUT);
  pinMode(pin_moist, INPUT);
  pinMode(pin_light_sensor, INPUT);
  pinMode(pin_hose, OUTPUT);
  pinMode(pinCS, OUTPUT);
  pinMode(pin_reset, OUTPUT_PULLUP)

  hatch.attach(pin_servo);

  SD.begin();
  rtc.begin();
  term.begin();

  for (int pos = 0; pos <= 180; pos++) {
    hatch.write(pos);
    delay(50);
  }
  hatch_state = "open";

  logged_state = false;

  new_day();

}

void loop() {

  t = rtc.getTime();
  X = t.hour + (t.min)*100/60;

  if (X == 0.0) {
    new_day();
  }

  //precisa fazer um sistema em que water_start() dependa de moist()
  //ai muda o tempo que a agua fica ligada (+ ou - tempo)
  if (X == 6.0 && moist() <= min_moist) { //por 10 min só (?) ou depende da mosit
    water_start();
} else if (X >= 6.166 || moist > max_moist) {
    water_stop();
  }

  if (t.min == 0) { //troca de hora
    long ideal_light = sin((X-6)*3.1416/12); //converter p lux
    if ( (temp() <= min_temp) && (lux() < ideal_light * 0.) {
      hatch_close();
    } else {
      hatch_open();
    }
  }

  if (hatch_state == "closed") {
    luz();
  } else {
    luz_stop();
  }

  // Um log a cada 10 minutos
  if ((t.min)%10 == 0 && logged_state == false) {
    log_data();
  } else if ((t.min)%10 != 0 && logged_state == true) {
    logged_state == false;
  }

}

void moist() {

  float moist, humidity;

  for (int i = 0; i < 100; i++) {
    humidity += analogRead(pin_moist);
    delay(1);
  }

  moist = 57.7638 * pow(2.73, 0.0068055 * humidity);

  if (moist > 100) {
    moist = 100;
  } else if (moist < 0) {
    moist = 0;
  }

  return moist;
}

float temp() {

  term.requestTemperatures();
  temp = term.getTempCByIndex(0);

  retrun temp;

}

long lux() { //falta converter a unidade

  long luz;

  luz = analogRead(pin_light_sensor);

  return luz;
}

void water_start() {

  digitalWrite(pin_hose, HIGH);

}

void water_stop() {

  digitalWrite(pin_hose, HIGH);

}

void luz_start() {

  t = rtc.getTime();

  X = t.hour + (t.min)*1/60;

  f = 255.5*sin((X-6)*3.1416/12);

  digitalWrite(pin_relay, HIGH);

  if (f <= 0) {
    f = 0;
    digitalWrite(pin_relay, LOW);
  }

  analogWrite(pin_led, f);

}

void luz_stop() {

  digitalWrite(pin_relay, LOW)

}

void log_data() {

  t = rtc.getTime
  myFile = SD.open("Freya_data_" + rtc.getDateStr() + ".txt")

  if (myFile) {
    myFile.print(X);
    myFile.print(",");
    myFile.print(lux());
    myFile.print(",");
    myFile.print(temp());
    myFile.print(",");
    myFile.println(moist());
    myFile.close();
  }

  logged_state = true;

}

void new_day() {

  t = rtc.getTime();

  if (SD.begin()) {
    myFile = SD.open("Freya_data_" + rtc.getDateStr() + ".txt")
    if (myFile) {
      myFile.println("");
      myFile.println("TIME(H.M(%)),LIGHT(%),SOIL_TEMPERATURE(ºC),SOIL_MOISTURE(%)");
      myFile.close();
    }
  }

}

void hatch_open() {

  for (int pos = 0; pos <= 180; pos++) {
    hatch.write(pos);
    delay(50);
  }
  hatch_state = "opened";

}

void hatch_close() {

  for (int pos = 180; pos >= 0; pos--) {
    hatch.write(pos);
    delay(50);
  }
  hatch_state = "closed";

}
