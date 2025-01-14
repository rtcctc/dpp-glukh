#define LED1_PIN 5
#define LED2_PIN 6
#define PHOTORESISTOR1_PIN A0
#define PHOTORESISTOR2_PIN A1

int sensorValue1 = 0;
int sensorValue2 = 0;

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue1 = analogRead(PHOTORESISTOR1_PIN);
  sensorValue2 = analogRead(PHOTORESISTOR2_PIN);

  analogWrite(LED1_PIN, map(sensorValue1, 0, 1023, 0, 255));
  analogWrite(LED2_PIN, map(sensorValue2, 0, 1023, 0, 255));

  if (sensorValue1 < 900 || sensorValue2 < 900) {
    Serial.print("launchAnimation;separately;5000#");
  } else if (sensorValue1 > 900 && sensorValue2 > 900) {
    Serial.print("launchAnimation;together;3000#");
  }

  delay(100); // 10 Hz
}
