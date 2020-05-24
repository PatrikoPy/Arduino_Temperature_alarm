#define AREF_VOLTAGE 3.3
#define TEMP_SENSOR_PIN  5
#define BUTTON_PIN_L 12
#define BUTTON_PIN_P 13
#define ALERT_PIN 2

float temperature;
unsigned short alert5 = 0;
unsigned short buzzerOff = 0;
unsigned short buttonStateL = 0;
unsigned short buttonStateP = 0;

void ledClear()
{
  for (short p = 2; p < 12; p++)
  {
    digitalWrite(p, LOW);
  }
}
void ledAll()
{
  for (short p = 2; p < 12; p++)
  {
    if (buzzerOff == 1 & p == 2) {
      continue;
    }
    digitalWrite(p, HIGH);
  }
}
float checkTemperature()
{
  int tempReading = analogRead(TEMP_SENSOR_PIN);
  float voltage = tempReading * AREF_VOLTAGE;
  voltage /= 1024.0;
  // Convert from 10 mv per degree with 500 mV offset to degrees celsius
  // ((voltage - 500mV) * 100)
  float temperatureC = (voltage - 0.5) * 100 ;
  Serial.println(temperatureC);
  // Delay for sensor to stabilize
  delay(1000);
  return temperatureC;
}
void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  for (int i = 2; i < 12; i++)
  {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON_PIN_L, INPUT);
  pinMode(BUTTON_PIN_P, INPUT);
}

void loop() {
  temperature = checkTemperature();
  buttonStateL = digitalRead(BUTTON_PIN_L);
  buttonStateP = digitalRead(BUTTON_PIN_P);

  if (temperature > 26.0)
  {
    Serial.println(buttonStateL);
    Serial.println(buttonStateP);
    if (buttonStateL == HIGH | buttonStateP == HIGH)
    {
      buzzerOff = 1;
      ledClear();
    }

    if (alert5 < 5)
    {
      digitalWrite(ALERT_PIN, LOW);
      delay(100);
      digitalWrite(ALERT_PIN, HIGH);
      alert5++;
    }
    else
    {
      ledAll();
    }

  }
  else
  {
    ledClear();
    buzzerOff = 0;
    alert5 = 0;
  }
}
