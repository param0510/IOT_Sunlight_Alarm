// Name: Paramveer Singh
// Date: 9/12/21
// Desription: This is the slave Arduino which is responsible for the user interface of the alarm clock.

// Including the Wire and LCD libraries.
#include <Wire.h>
#include <LiquidCrystal.h>

// setting up the LCD.
LiquidCrystal lcd(7,6,5,4,3,2);

// defining notes for the buzzer music.
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

// This is a 2-D array which contains the songs' notes as well as their duration data.
int melody[][200] = {

  // Song Name: Wiegenlied (Brahms' Lullaby)
  // Snippet source: https://github.com/robsoncouto/arduino-songs/blob/master/brahmslullaby/brahmslullaby.ino
 {
  NOTE_G4, 4, NOTE_G4, 4, //1
  NOTE_AS4, -4, NOTE_G4, 8, NOTE_G4, 4,
  NOTE_AS4, 4, REST, 4, NOTE_G4, 8, NOTE_AS4, 8,
  NOTE_DS5, 4, NOTE_D5, -4, NOTE_C5, 8,
  NOTE_C5, 4, NOTE_AS4, 4, NOTE_F4, 8, NOTE_G4, 8,
  NOTE_GS4, 4, NOTE_F4, 4, NOTE_F4, 8, NOTE_G4, 8,
  NOTE_GS4, 4, REST, 4, NOTE_F4, 8, NOTE_GS4, 8,
  NOTE_D5, 8, NOTE_C5, 8, NOTE_AS4, 4, NOTE_D5, 4,

  NOTE_DS5, 4, REST, 4, NOTE_DS4, 8, NOTE_DS4, 8, //8
  NOTE_DS5, 2, NOTE_C5, 8, NOTE_GS4, 8,
  NOTE_AS4, 2, NOTE_G4, 8, NOTE_DS4, 8,
  NOTE_GS4, 4, NOTE_AS4, 4, NOTE_C5, 4,
  NOTE_AS4, 2, NOTE_DS4, 8, NOTE_DS4, 8,
  NOTE_DS5, 2, NOTE_C5, 8, NOTE_GS4, 8,
  NOTE_AS4, 2, NOTE_G4, 8, NOTE_DS4, 8,
  NOTE_AS4, 4, NOTE_G4, 4, NOTE_DS4, 4,
  NOTE_DS4, 2
 },
 
  // Song Name: Jigglypuff's Song
  // Snippet source: https://github.com/robsoncouto/arduino-songs/commit/e9694fdf651d53087fe7bd925e35428ab2c0654f
 {
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
  NOTE_D5,-2,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-1,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,

  NOTE_FS5,-4, NOTE_E5,8, NOTE_FS5,4,
  NOTE_D5,-2,
  NOTE_D5,-4, NOTE_A5,8, NOTE_FS5,8, NOTE_D5,8,
  NOTE_E5,-4, NOTE_FS5,8, NOTE_G5,4,
  NOTE_FS5,-1
 },
   
  // Song Name: Nokia Ringtone 
  // Snippet source: https://github.com/robsoncouto/arduino-songs/commit/3a9137a835e37caeb8d547f48b9d1c0532644526 
 {
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2, 
   
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2,
   
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4, 
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4, 
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2,
 }
  
};

// This is tempo data for each of the songs which can be changed to change the speed of the song being played.
int tempo[] = {76, 85, 140};

// variables required to play the songs through the buzzer.
int divider = 0, noteDuration = 0;

// setting up the buzzer pin values.
int buzzerPin = 12;

// variables to store the values being received from the master Arduino.
int choice;
int alarm = 0;
int songChange = 0;
int remote;

void setup()
{
  // code linking the master and slave arduino.
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
  
  // Setting up the functionalities being used in the slave arduino.
  lcd.begin(16,2);
  pinMode(buzzerPin, OUTPUT);
  
  // Enabling serial monitor.
  Serial.begin(9600);
}

void loop()
{
  delay(100);
  
  // playing song when the alarm goes off. 
  if(alarm == 1 && remote == 1)
  {
    playSong(choice - 1);
  }
}

void receiveEvent(int howMany)
{
  // Receiving values from the master arduino.
  choice = Wire.read();
  alarm = Wire.read();
  remote = Wire.read();
  songChange = Wire.read();

  // Clearing the LCD Screen.
  lcd.clear();
  
  // Printing good morning message when the alarm turns on.
  if(alarm == 1 && remote == 1)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Good Morning!");
    lcd.setCursor(0,1);
    lcd.print("Time to wake up");
  }
  
  // Displaying the song name on changing the rotation pin dial.
  if(alarm == 0 && songChange !=0)
  {
    lcd.clear();
    
    switch(choice)
    {
      case 1:
        lcd.setCursor(0,0);
        lcd.print("Wiegenlied");
        delay(500);
        break;
      case 2:
        lcd.setCursor(0,0);
        lcd.print("Jigglypuff");
        delay(500);
        break;
      default:
        lcd.setCursor(0,0);
        lcd.print("Nokia");
        delay(500);
    }
  }
  
  // Turning off the alarm when the power button is pressed on the IR Remote.
  if( remote == 0)
  {
    // stop the waveform generation before the next note.
    noTone(buzzerPin);
    
    // termination of the program.
    exit(0);
  }
}

// Playing songs according to the user's choice a night before setting up the alarm.
void playSong(int songNo)
{
  // I combined this code with what I have used in my project, but still it is quite similar to the source, so I mentioned its source anyway.
  // Code Source: https://github.com/robsoncouto/arduino-songs/commit/e9694fdf651d53087fe7bd925e35428ab2c0654f
  
  int notes = ( sizeof(melody[songNo]) / sizeof(int) ) / 2;

  int wholenote = (90000) / tempo[songNo];
  
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) 
  {
    // calculates the duration of each note
    divider = melody[songNo][thisNote + 1];
    
    if (divider > 0) 
    {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } 
    else if (divider < 0) 
    {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzerPin, melody[songNo][thisNote], noteDuration * 0.8);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);
  }
}

