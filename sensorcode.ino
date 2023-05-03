#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char auth[] = "";//Enter your Auth token
char ssid[] = "";//Enter your WIFI name
char pass[] = "";//Enter your WIFI password

BlynkTimer timer;

#define RAIN_SENSOR_PIN A0
#define RAIN_SENSOR_THRESHOLD 850 // adjust this value based on your sensor
const int redLED = D3;
const int buzpin = D5; // change this to a different pin if necessary
int flag = 0;
#define VPIN_BUTTON_2 V1

#define ON HIGH
#define OFF LOW

void setup()
{
  pinMode(D3, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  int sensorValue = analogRead(RAIN_SENSOR_PIN);
  Serial.print("Rain sensor value: ");
  Serial.println(sensorValue);

  if (sensorValue < RAIN_SENSOR_THRESHOLD) {
    Blynk.logEvent("test_rain");
    Blynk.virtualWrite(VPIN_BUTTON_2, "Water Level is Above Average !!");
    digitalWrite(redLED, HIGH);
    digitalWrite(D3, HIGH);
    tone(buzpin, 50);
    flag = 1;
  }
  else {
    flag = 0;
    noTone(buzpin); // make sure this function is called
    digitalWrite(redLED, LOW);
    digitalWrite(D3, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_2, "Water Level is Normal");
  }

  Blynk.virtualWrite(V0, sensorValue);

  Blynk.run();
  delay(1000);
}
