/*
	Simple application to mute your microphone using Arduino Pro Micro and NicoHood/HID Library
	
	In the end, this is just a custom button which emulates a key sequence.
	There are two buttons available where you can map common mute shortkeys to individualy.
	
	TODO: Track https://github.com/NicoHood/HID/issues/151 for possible progress of LED_MICROPHONE
*/

#include "Arduino.h"
#include "HID-Project.h"


/*	Following mappings are available to assign to buttons individual:
	0 -> WIN + F4 (e.g. Skype)
	1 -> CTRL + m (e.g. WebEx)
	2 -> M (e.g. Jitsy)
	3 -> ALT + a (e.g. Zoom)
	4 -> F20 (e.g. Linux XF86AudioMicMute)
*/
#define PRIMARY_BUTTON_KEY_MAPPING		0
#define SECONDARY_BUTTON_KEY_MAPPING	0


const uint8_t statusLed = LED_BUILTIN;	// LED indicating that button is pressed
const uint8_t primaryButton = 2;				// Primary button
const uint8_t secondaryButton = 3;			// Secondary button

void sendMuteMicKeys(const uint8_t mapping)
{
	switch (mapping)
	{
		default:
			//[[fallthrough]];
		case 0:
			Keyboard.press(KEY_LEFT_GUI);
			Keyboard.press(KEY_F4);
			break;
			
		case 1:	
			Keyboard.press(KEY_LEFT_CTRL);
			Keyboard.press('m');
			break;
			
		case 2:
			Keyboard.press('M');
			break;
			
		case 3:
			Keyboard.press(KEY_LEFT_ALT);
			Keyboard.press('a');
			break;
			
		case 4:
			Keyboard.write(KEY_F20);
			break;
	}	 
	delay(100);
	Keyboard.releaseAll();
}

void setup() {
	// Start emulating keyboard
	Keyboard.begin();

	// Initialise I/O
	pinMode(statusLed, OUTPUT);
	pinMode(primaryButton, INPUT_PULLUP);
	pinMode(secondaryButton, INPUT_PULLUP);
}

void loop() {
	// Handle primary button
	if (!digitalRead(primaryButton)) {
		digitalWrite(statusLed, HIGH);
		sendMuteMicKeys(PRIMARY_BUTTON_KEY_MAPPING);
		while (!digitalRead(primaryButton)) {
			delay(100);
		}
		digitalWrite(statusLed, LOW);
	}

	// Handle secondary button
	if (!digitalRead(secondaryButton)) {
		digitalWrite(statusLed, HIGH);
		sendMuteMicKeys(SECONDARY_BUTTON_KEY_MAPPING);
		while (!digitalRead(secondaryButton)) {
			delay(100);
		}
		digitalWrite(statusLed, LOW);
	}
}

