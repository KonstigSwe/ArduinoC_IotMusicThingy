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
const int BUZZER_PIN = 13;

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

char holdKey;
unsigned long t_hold;

void setup() {
	pinMode(BUZZER_PIN, OUTPUT);
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
	char key = keypad.getKey();
	//if (key) {
		/*holdKey = key;*/

		//if (keypad.getState() == HOLD) {
			//if (millis() - t_hold > 100) {
			/*	switch (holdKey) {
				case '1':
					tone(BUZZER_PIN, 420, 100);
					break;
				case '2':
					tone(BUZZER_PIN, 840, 100);
					break;
				}*/
			//}
		//}
		//tone(BUZZER_PIN, 432, 500);
		//Serial.println(key);'
	for (int n = 0; n < LIST_MAX; ++n) {
		if (keypad.key[n].stateChanged) {
			Serial.print(keypad.key[n].kstate);
			switch (keypad.key[n].kstate) {
			case PRESSED :
				//tone(BUZZER_PIN);
				Serial.write("Pressed");
				tone(BUZZER_PIN, 420 + random(100, 1000));
				break;
			case HOLD: 
				Serial.write("Hold Tha Door");
				tone(BUZZER_PIN, 420 + random(100, 1000));
				break;
			case IDLE:
				noTone(BUZZER_PIN);
				Serial.write("idle");
				break;
			default:
				noTone(BUZZER_PIN);
				break;
			}
		}
	}
		/*switch (key) {
		case '1':
			tone(BUZZER_PIN, NOTE_C4, 150);
			break;
		case '2':
			tone(BUZZER_PIN, NOTE_CS4, 150);
			break;
		case '3':
			tone(BUZZER_PIN, NOTE_D4, 150);
			break;
		case 'A':
			tone(BUZZER_PIN, NOTE_DS4, 150);
			break;
		case '4':
			tone(BUZZER_PIN, NOTE_E4, 150);
			break;
		case '5':
			tone(BUZZER_PIN, NOTE_F4, 150);
			break;
		case '6':
			tone(BUZZER_PIN, NOTE_FS4, 150);
			break;
		case 'B':
			tone(BUZZER_PIN, NOTE_G4, 150);
			break;
		case '7':
			tone(BUZZER_PIN, NOTE_GS4, 150);
			break;
		case '8':
			tone(BUZZER_PIN, NOTE_A4, 150);
			break;
		case '9':
			tone(BUZZER_PIN, NOTE_AS4, 150);
			break;
		case 'C':
			tone(BUZZER_PIN, NOTE_B4, 150);
			break;
		}*/
	//}
}
