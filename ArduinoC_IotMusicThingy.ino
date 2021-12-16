/*
 Name:		ArduinoC_IotMusicThingy.ino
 Created:	12/13/2021 9:29:37 AM
 Author:	nikla
*/

#include <Keypad.h>
#include <Key.h>
#include "pitches.h"

const unsigned int SECONDS_PER_MINUTE = 60u;
const unsigned int MILLISECONDS_PER_SECOND = 1000u;

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

struct note {
	unsigned int frequency;
	unsigned int duration;
	unsigned int delay; //tone() doesn't wait for previous note to finish, so we manually wait a while.
};

//Ugly hardcoded melodies
void flamingo() {
	const unsigned int BPM = 89u;
	const unsigned int t4th = MILLISECONDS_PER_SECOND * SECONDS_PER_MINUTE / BPM; //quarter note length (ms)
	const unsigned int t8th = t4th / 2u;
	const unsigned int t16th = t8th / 2u;
	const unsigned int t32nd = t16th / 2u;

	note notes[]{
		//Bar 1 / 5
		{NOTE_GS4, t16th, t16th}, {NOTE_AS4, t16th, t16th}, {NOTE_C5, t16th, t16th}, {NOTE_DS5, t16th, t8th},
		{NOTE_F5, t16th, t8th},	{NOTE_F5, t32nd, t32nd}, {NOTE_G5, t32nd, t32nd}, {NOTE_F5, t16th, t8th},
		{NOTE_DS5, t16th, t8th}, {NOTE_C5, t16th, t8th}, {NOTE_F5, t16th, t8th},
		//Bar 2 / 6
		{NOTE_DS5, t8th, t16th*3}, {NOTE_G4, t16th, t16th}, {NOTE_GS4, t16th, t16th}, {NOTE_AS4, t16th, t16th},
		{NOTE_C5, t16th, t16th}, {NOTE_DS5, t16th, t8th}, {NOTE_F5, t16th, t8th}, {NOTE_F5, t32nd, t32nd},
		{NOTE_G5, t32nd, t32nd}, {NOTE_F5, t16th, t8th}, {NOTE_DS5, t16th, t8th},
		//Bar 3 / 7
		{NOTE_D5, t4th, t4th}, {NOTE_AS4, t8th, t16th*3}, {NOTE_G4, t16th*1.5, t8th}, {NOTE_C5, t16th, t16th},
		{NOTE_G4, t16th, t16th}, {NOTE_C5, t16th, t16th}, {NOTE_AS4, t8th, t16th*3}, {NOTE_G4, t16th, t32nd}, {NOTE_FS4, t16th, t32nd},
		//Bar 4
		{NOTE_F4, t16th, t16th}, {NOTE_GS4, t16th, t16th}, {NOTE_DS5, t16th, t16th}, {NOTE_F4, t16th, t16th},
		{NOTE_GS4, t16th, t16th}, {NOTE_DS5, t16th, t16th}, {NOTE_F4, t16th, t16th}, {NOTE_DS5, t16th, t16th},
		{NOTE_DS5, t16th, t16th}, {NOTE_F4, t16th, t16th}, {NOTE_DS5, t16th, t16th}, {NOTE_F4, t16th, t16th},
		{NOTE_DS5, t16th, t16th}, {NOTE_F4, t16th, t16th}, {NOTE_G4, t16th, t16th}, {NOTE_AS4, t16th, t16th},
		//Bar 8
		{NOTE_F4, t16th, t16th}, {NOTE_GS4, t16th, t16th}, {NOTE_DS5, t16th, t16th}, {NOTE_F4, t16th, t16th},
		{NOTE_C5, t16th, t8th}, {NOTE_D5, t16th, t8th}, {NOTE_DS5, t8th, t8th}
	};

	//Bars 1-4
	for (int i = 0; i < 47; i++)
	{
		tone(BUZZER_PIN, notes[i].frequency, notes[i].duration);
		delay(notes[i].delay);
	}
	//Bars 5-7 (repetitions of 1-3)
	for (int i = 0; i < 31; i++)
	{
		tone(BUZZER_PIN, notes[i].frequency, notes[i].duration);
		delay(notes[i].delay);
	}
	//Bar 8
	for (int i = 47; i < 54; ++i) {
		tone(BUZZER_PIN, notes[i].frequency, notes[i].duration);
		delay(notes[i].delay);
	}
}

void rickroll() {
	const unsigned int BPM = 110;
	const unsigned int t4th = MILLISECONDS_PER_SECOND * SECONDS_PER_MINUTE / BPM; //quarter note length (ms)
	const unsigned int t8th = t4th / 2u;
	const unsigned int t16th = t8th / 2u;
	//const unsigned int t32nd = t16th / 2u;

	note intro[]{
		{NOTE_CS5, t4th * 1.5, t4th * 1.5}, {NOTE_DS5, t4th * 1.5, t4th * 1.5}, {NOTE_GS4, t4th, t4th},
		{NOTE_DS5, t4th * 1.5, t4th * 1.5}, {NOTE_F5, t4th * 1.5, t4th * 1.5},
		{NOTE_GS5, t16th, t16th}, {NOTE_FS5, t16th, t16th}, {NOTE_F5, t8th, t8th},
		{NOTE_CS5, t4th * 1.5, t4th * 1.5}, {NOTE_DS5, t4th * 1.5, t4th * 1.5}, {NOTE_GS4, t4th * 2, t4th * 5},
	};
	/*note verse[]{
		{NOTE_AS4, t8th, t8th}, {NOTE_C5, t8th, t8th}, {NOTE_CS5, t8th, t8th}, {NOTE_CS5, t8th, t8th},
		{NOTE_DS5, t8th, t8th}, {NOTE_C5, t8th * 1.5, t8th * 1.5}, {NOTE_AS4, t16th, t16th}, {NOTE_GS4, t4th, t4th * 4 + t8th},


	};
	note chorus[]{
		{}
	};*/

	for (note n : intro) {
		tone(BUZZER_PIN, n.frequency, n.duration);
		delay(n.delay);
	}
	//Not a mistake; play it twice.
	for (note n : intro) {
		tone(BUZZER_PIN, n.frequency, n.duration);
		delay(n.delay);
	}
	/*delay(t4th);
	for (note n : verse) {
		tone(BUZZER_PIN, n.frequency, n.duration);
		delay(n.delay);
	}
	for (note n : chorus) {
		tone(BUZZER_PIN, n.frequency, n.duration);
		delay(n.delay);
	}*/
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
			note = NOTE_B3;
			break;
		case '0':
			flamingo();
			return;
		case '#':
			rickroll();
			return;
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
