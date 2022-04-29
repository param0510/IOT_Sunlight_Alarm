// Name: Paramveer Singh
// Date: 9/12/21
// Desription: This is the master Arduino which acts as the brain of the alarm clock.

// including libraries for data transfer between master and slave Arduino
#include <Wire.h>

// data variables required by the master arduino
int lightSensorPin = A1;
int lightSensorData = 0;
int rotationPin = A0;
int rotationPinData = 0;
int songChoice = 0;
int alarm = 0;
int songChange = 0;
int lastSongChoice = 0;

// including the IR remote libraries
#include <IRremote.h>

// setting up the IR Remote receiver accordingly.
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

// value required to store the value received from the IR Remote.
int value = 0;

// flag variable required to switch of the alarm using the remote.
int remote = 1 ;

void setup()
{
  // Setting up all the devices accordingly.
  Wire.begin();
  pinMode(rotationPin, INPUT);
  
  // Enabling the serial monitor and the IR receiver.
  Serial.begin(9600);
  irrecv.enableIRIn();
}

void loop()
{
  // looking for remote button being pressed and storing the value accordingly.
  if (irrecv.decode(&results))
  {
    value = results.value;
    irrecv.resume(); // Receive the next value
  }
  
  // Statements for the power button being pressed.
  if( value == 255)
  {
    Serial.println(" ");
    Serial.println("*****************");
    Serial.print("Power Off.");
    Serial.println("*****************");
    remote = 0;
  }
  
  // Reading and maping the rotation pin value.
  rotationPinData = analogRead(rotationPin);
  songChoice = map(rotationPinData, 0, 1023, 1, 3);
  
  // checking for the change in song choice
  songChange = songChoice - lastSongChoice;
  delay(100);
  lastSongChoice = songChoice;

  // Reading and mapping the light sensor values.
  lightSensorData = analogRead(lightSensorPin);
  lightSensorData = map(lightSensorData, 6, 679, 0, 100);
  
  // enabling the flag value for turning on the alarm clock if the sunlight is sufficient enough.
  if (lightSensorData >70)
  {
    alarm = 1;
  }
  else
  {
    alarm = 0;
  }

  // Sending required values to the slave arduino.
  Wire.beginTransmission(4);
  Wire.write(songChoice);
  Wire.write(alarm);
  Wire.write(remote);
  Wire.write(songChange);
  Wire.endTransmission();
  
  delay(500);
}

