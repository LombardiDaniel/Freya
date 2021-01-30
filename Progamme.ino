/*

Needs Fixing:
    linha 84~90 fazer com testes
    linha 145~152 (luz)- descobrir o valor máximo que da pra ter
        e usar a função map(value, fromLow, fromHigh, toLow, toHigh)
    adicionar o lance de longitute e latitude (fazer site com cidade?)

*/

#include <DallasTemperature.h>
#include <OneWire.h>
#include <DS3231.h>
#include <Servo.h>
#include <SD.h>
#include <SPI.h>

#define pin_temp 2
#define pin_moist //must be analog
#define pin_light_sensor //must be analog
#define pin_hose //must be digital
#define pin_CS //must be analog
#define pin_reset //must be analog
#define pin_relay //must be digital
#define pin_servo //must be PWM

const int steps = 2038; // depends on the stepper motor
const float rot_speed = 9; // optimized speed that I found
const int min_moist; // must be between 0-100 (%)
const int max_moint; // must be between 0-100 (%) and higher than min_moist
const int min_temp; // in Celsius
float X; // Counter of hours and minutes (decimal based, `13h30` is `13.5`)
char hatch_state[]; // hatch state


File myFile;
OneWire oneWire(pin_temp);
DallasTemperature term(&oneWire);
Servo hatch;
Time t;
DS3231 rtc(SDA, SCL);


float moist();
float temp();
float lux();
void water_start();
void water_stop();
void luz_start();
void luz_stop();
void log_data();
void new_day();
void hatch_open();
void hatch_close();


void setup() {

    pinMode(pin_temp, INPUT);
    pinMode(pin_moist, INPUT);
    pinMode(pin_light_sensor, INPUT);
    pinMode(pin_hose, OUTPUT);
    pinMode(pin_CS, OUTPUT);
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


    /*precisa fazer um sistema em que water_start() dependa de moist()
    ai muda o tempo que a agua fica ligada (+ ou - tempo)*/
    if (X == 6.0 && moist() <= min_moist) //por 10 min só (?) ou depende da mosit
        water_start();
    else if (X >= 6.166 || moist > max_moist)
        water_stop();


    if (t.min == 0) { //troca de hora

        long ideal_light = sin((X-6)*3.1416/12); //converter p lux e achar valor de % (no momento é 0.6)

        if ((temp() <= min_temp) && (lux() < ideal_light * 0.6)
            hatch_close();
        else
            hatch_open();

    }

    if (hatch_state == "closed")
        luz_start();
    else
        luz_stop();


    // Um log a cada 10 minutos
    if ((t.min)%10 == 0 && logged_state == false)
        log_data();
    else if ((t.min)%10 != 0 && logged_state == true)
        logged_state == false;


}

float moist() {

    float moist, humidity;

    for (int i = 0; i < 100; i++) {
        humidity += analogRead(pin_moist);
        delay(1);
    }

    moist = 57.7638 * pow(2.73, 0.0068055 * humidity);

    if (moist > 100)
        moist = 100;
    else if (moist < 0)
        moist = 0;


    return moist;
}

float temp() {

    term.requestTemperatures();
    temp = term.getTempCByIndex(0);

    retrun temp;

}

float lux() {

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
    myFile = SD.open("freya_data_" + rtc.getDateStr() + ".txt")

    if (myFile) {
        myFile.print("%.2f,%s,%.2f,%.2f,%.2f\n", X, hatch_state, lux(), temp(), moist());
        myFile.close();
    }

    logged_state = true;

}

void new_day() {

    t = rtc.getTime();

    if (SD.begin()) {
        myFile = SD.open("freya_data_" + rtc.getDateStr() + ".txt")
        if (myFile) {
            myFile.println("");
            myFile.println("TIME[H.M(decimal)],LIGHT[%],SOIL_TEMPERATURE[ºC],SOIL_MOISTURE[%]");
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
