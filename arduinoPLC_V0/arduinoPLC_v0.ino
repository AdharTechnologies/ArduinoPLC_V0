#include "config.h"

unsigned int R_pin;
String receivedString = "";

void setup() {
  Serial.begin(9600);

  //Declaring the pins 2-13 as OUTPUT
  for (int i=2; i<14; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW); // Set all pins initially to HIGH
  }

  Serial.println(version);
  delay(1000);

}

void loop() {
  if (Serial.available() > 0){
    char receivedChar = Serial.read();

    if (receivedChar != '\n'){
      receivedString += receivedChar;
    }
    else{
      if (receivedString.indexOf('-') != -1){
        //Dash is present, set pin HIGH. HIGH means RLY OFF
        R_pin = receivedString.substring(0, receivedString.indexOf('-')).toInt();
        digitalWrite(R_pin, HIGH);
        Serial.print("-"); Serial.println(R_pin);
      }
      else{
        //No dash present, set pin LOW. LOW means RLY ON
        R_pin = receivedString.toInt();
        digitalWrite(R_pin, LOW);
        Serial.println(R_pin);
      }

      // Reset the received string for the next input
      receivedString = "";
    }
  }
}
