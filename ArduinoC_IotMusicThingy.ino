/*
 Name:		ArduinoC_IotMusicThingy.ino
 Created:	12/13/2021 9:29:37 AM
 Author:	nikla
*/

#include <Keypad.h>
#include <Key.h>
#include "pitches.h"

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = { 9, 8, 7, 6 }; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = { 5, 4, 3, 2 }; //connect to the column pinouts of the keypad
// the setup function runs once when you press reset or power the board
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
void setup() {
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
	char key = ;
		
		if (!keypad.ispressed(key))
		{
			key = keypad.getKey();
			keypad.key->kstate;
			keypad.getState();
			
		} 

	if (key) {
		Serial.println(key);
	}
}
