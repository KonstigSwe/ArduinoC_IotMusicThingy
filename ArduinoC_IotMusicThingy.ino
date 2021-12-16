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

//Ugly hardcoded melodies

void flamingo() {
	//16th note at 89 BPM: 169 ms
	//bar 1
	int NoteArray[55]{ NOTE_GS4 ,NOTE_AS4 ,NOTE_C5,NOTE_DS5,NOTE_F5, NOTE_F5 ,NOTE_G5,NOTE_F5,NOTE_DS5,NOTE_C5,NOTE_F5,NOTE_DS5,NOTE_G4,NOTE_GS4,NOTE_AS4,NOTE_C5,NOTE_DS5,
		NOTE_F5,NOTE_F5 ,NOTE_G5,NOTE_F5 ,NOTE_DS5,NOTE_D5,NOTE_AS4,NOTE_AS4,NOTE_G4,NOTE_C5,NOTE_G4,NOTE_C5,NOTE_AS4,NOTE_D4,NOTE_DS4 ,NOTE_F4,NOTE_GS4,NOTE_DS5,NOTE_F4,NOTE_GS4,NOTE_DS5,NOTE_F4
	,NOTE_DS5,NOTE_DS5,NOTE_F4, NOTE_DS5,NOTE_F4,NOTE_AS4,NOTE_F4,NOTE_G4,NOTE_AS4, NOTE_F4, NOTE_GS4, NOTE_DS5, NOTE_F4, NOTE_C5, NOTE_D5, NOTE_DS5};
	int NoteTime[55]{ 169,169,169,169,169,169 / 2,169 / 2,169,169,169,169,169 * 2,169,169,169,169,169,169,169 / 2,169 / 2,169,169,169 * 4,169 * 2,169,169,169,169,169,169 * 2,169 / 2,169 / 2,
	169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169, 169, 169 , 169 , 169 , 169 , 169, 169*2};

	int DelayTime[55]{ 169,169,169,169 * 2,169 * 2,169 / 2,169 / 2,169 * 2,169 * 2,169 * 2,169 * 2,169 * 3,169,169,169,169,169 * 2,169 * 2,169 / 2,169 / 2,169 * 2,169 * 2,169 * 4
		,169 * 3,169,169,169,169,169,169 * 3,169 / 2,169 / 2,
	169,169,169,169,169,169,169,169,169,169,169,169,169,169,169,169, 169, 169, 169, 169, 169*2, 169 * 2, 169 * 2};
	for (int i = 0; i <48; i++)
	{
		tone(BUZZER_PIN, NoteArray[i], NoteTime[i]);
		delay(DelayTime[i]);
	}
	for (int i = 0; i < 32; i++)
	{
		tone(BUZZER_PIN, NoteArray[i], NoteTime[i]);
		delay(DelayTime[i]);
	}
	for (int i = 48; i < 55; ++i) {
		tone(BUZZER_PIN, NoteArray[i], NoteTime[i]);
		delay(DelayTime[i]);
	}
}

void setup() {
	pinMode(BUZZER_PIN, OUTPUT);
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
	char key = keypad.getKey();

	if (keypad.keyStateChanged()) {
		int note;
		Serial.print(key);
		switch (key) {
		case '1':
			note = NOTE_C4;
			break;
		case '2':
			note = NOTE_CS4;
			break;
		case '3':
			note = NOTE_D4;
			break;
		case 'A':
			note = NOTE_DS4;
			break;
		case '4':
			note = NOTE_E4;
			break;
		case '5':
			note = NOTE_F4;
			break;
		case '6':
			note = NOTE_FS4;
			break;
		case 'B':
			note = NOTE_G4;
			break;
		case '7':
			note = NOTE_GS4;
			break;
		case '8':
			note = NOTE_A4;
			break;
		case '9':
			note = NOTE_AS4;
			break;
		case 'C':
			note = NOTE_B4;
			break;
		case '*':
			flamingo();
			break;
		}

		switch (keypad.getState()) {
		case PRESSED:
			tone(BUZZER_PIN, note);
			break;
		case RELEASED:
			noTone(BUZZER_PIN);
			break;
		}
	
	}
}
