#include <DHT.h> // DHT sensor library for temperature and humidity
#include <Servo.h> // Servo motor library for controlling louvers
#include <Wire.h> // I2C communication library
#include <BH1750.h> // BH1750 light sensor library for measuring light intensity

#define DHTPIN1 2 // Pin for DHT11 sensor
#define DHTTYPE DHT11 // Type of DHT sensor used
#define SERVOPIN1 9 // Pin for the first servo motor
#define SERVOPIN2 10 // Pin for the second servo motor
#define SERVOPIN3 11 // Pin for the third servo motor

DHT dht1(DHTPIN1, DHTTYPE); // Initialize DHT sensor
Servo myservo1, myservo2, myservo3; // Initialize servo motors
BH1750 lightMeter; // Initialize light sensor

void setup() {
  Serial.begin(9600); // Start serial communication
  Wire.begin(); // Start I2C communication
  myservo1.attach(SERVOPIN1); // Attach servos to their pins
  myservo2.attach(SERVOPIN2); 
  myservo3.attach(SERVOPIN3); 
  dht1.begin(); // Start DHT sensor
  lightMeter.begin(); // Start light sensor
  Serial.println(F("Adaptive Facade System Initialization"));
}

void loop() {
  delay(1000); // Measurement interval of 1 second

  float temp1 = dht1.readTemperature(); // Measure temperature
  float lux = lightMeter.readLightLevel(); // Measure light intensity

  if (isnan(temp1)) {
    Serial.println("Error reading temperature"); // Handle failed temperature reading
  } else {
    Serial.print("Temperature: ");
    Serial.print(temp1, 1);
    Serial.println(" °C");
    Serial.print("Light: ");
    Serial.print(lux);
    Serial.println(" lx");

    int servoPosition; // Determine louver position
    // Close louvers if temperature is above 25°C
    if (temp1 > 25) {
      servoPosition = 90;
    // Open louvers if temperature is 25°C or below and light intensity is within optimal range
    } else if (temp1 <= 25 && lux >= 100 && lux <= 3000) {
      servoPosition = 0;
    } else {
      servoPosition = 90; // Default to closed louvers
    }

    // Apply the determined position to all servo motors controlling the louvers
    myservo1.write(servoPosition);
    myservo2.write(servoPosition);
    myservo3.write(servoPosition);
  }
}
