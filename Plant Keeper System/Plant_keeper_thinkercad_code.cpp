// Define pins for RGB LEDs
const int lightRedPin = 3, lightGreenPin = 5, lightBluePin = 6;
const int soilRedPin = 9, soilGreenPin = 10, soilBluePin = 11;
const int tempRedPin = 7, tempGreenPin = 8, tempBluePin = 12;

// Sensor pins
const int lightSensorPin = A0;
const int soilMoisturePin = A1;
const int tempSensorPin = A2;

// Thresholds for sensors
const int lightThreshold = 500;
const int soilThreshold = 300;
const float tempMin = 15;       // Minimum temperature in Celsius
const float tempMax = 30;       // Maximum temperature in Celsius

void setup() {
  // Set RGB LED pins as outputs
  pinMode(lightRedPin, OUTPUT);
  pinMode(lightGreenPin, OUTPUT);
  pinMode(lightBluePin, OUTPUT);

  pinMode(soilRedPin, OUTPUT);
  pinMode(soilGreenPin, OUTPUT);
  pinMode(soilBluePin, OUTPUT);

  pinMode(tempRedPin, OUTPUT);
  pinMode(tempGreenPin, OUTPUT);
  pinMode(tempBluePin, OUTPUT);

  // Initialize Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read sensor values
  int lightValue = analogRead(lightSensorPin);
  int soilValue = analogRead(soilMoisturePin);
  int tempValue = analogRead(tempSensorPin);

  // Convert temperature sensor reading to Celsius
  float temperature = (tempValue * 5.0 / 1023) * 100;

  // Light Sensor RGB LED Logic
  analogWrite(lightRedPin, 0);
  analogWrite(lightGreenPin, 0);
  analogWrite(lightBluePin, 255); // Default Blue

  if (lightValue < lightThreshold) {
    analogWrite(lightRedPin, 255); // Turn Red on for low light
    analogWrite(lightBluePin, 0);  // Turn Blue off
  }

  // Soil Moisture RGB LED Logic
  analogWrite(soilRedPin, 0);
  analogWrite(soilGreenPin, 0);
  analogWrite(soilBluePin, 255); // Default Blue

  if (soilValue < soilThreshold) {
    analogWrite(soilRedPin, 255); // Turn Red on for dry soil
    analogWrite(soilBluePin, 0);  // Turn Blue off
  }

  // Temperature RGB LED Logic
  analogWrite(tempRedPin, 0);
  analogWrite(tempGreenPin, 0);
  analogWrite(tempBluePin, 255); // Default Blue

  if (temperature < tempMin || temperature > tempMax) {
    analogWrite(tempRedPin, 255); // Turn Red on for out-of-range temperature
    analogWrite(tempBluePin, 0);  // Turn Blue off
  }

  // Print sensor values for debugging
  Serial.print("Light Sensor Value: ");
  Serial.println(lightValue);
  Serial.print("Soil Moisture Value: ");
  Serial.println(soilValue);
  Serial.print("Temperature (Celsius): ");
  Serial.println(temperature);

  delay(1000); // 1-second delay
}

