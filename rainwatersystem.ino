// Defining Blynk Template ID, Name, and Authentication Token
// Add your own Blynk Credentials here
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

// Including necessary libraries
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Initializing Blynk authentication and Wi-Fi credentials
// Add your own WiFi credentials here
char auth[] = ""; // Enter your Auth token
char ssid[] = "";//Enter your WIFI name
char pass[] = "";//Enter your WIFI password

// Initializing variables and pins
BlynkTimer timer;
#define RAIN_SENSOR_PIN A0
#define RAIN_SENSOR_THRESHOLD 850 // Adjust this value based on your sensor
const int redLED = D3;
const int buzpin = D5; // Change this to a different pin if necessary
const int buzzpin = D6;
int flag = 0;
#define VPIN_BUTTON_2 V1

#define ON HIGH
#define OFF LOW

void setup()
{
  pinMode(D3, OUTPUT);
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass); // Starting Blynk connection using Wi-Fi credentials

}

void loop()
{
  int sensorValue = analogRead(RAIN_SENSOR_PIN);
  Serial.print("Rain sensor value: ");
  Serial.println(sensorValue);

  // Checking if rain sensor value is below the threshold
  if (sensorValue < RAIN_SENSOR_THRESHOLD) {
    Blynk.logEvent("alert"); // Logging the event in the Blynk app
    Blynk.virtualWrite(VPIN_BUTTON_2, "Rainfall has been detected in monitored locations!"); // Writing a message in the Blynk app
    digitalWrite(redLED, HIGH);
    digitalWrite(D3, HIGH);
    tone(buzpin, 100); // Emitting a tone using buzzer
    tone(buzzpin,100);
    flag = 1;
  }
  else {
    flag = 0;
    noTone(buzpin);
    noTone(buzzpin); // Stopping the tones emitted by the buzzer
    digitalWrite(redLED, LOW);
    digitalWrite(D3, LOW);
    Blynk.virtualWrite(VPIN_BUTTON_2, "No rainfall detected"); // Writing a message in the Blynk app
  }

  // Sending sensor value to the Blynk app
  Blynk.virtualWrite(V0, sensorValue);
  Blynk.virtualWrite(V2, sensorValue);

  // Running the Blynk connection and adding a delay
  Blynk.run();
  delay(1000);
}

