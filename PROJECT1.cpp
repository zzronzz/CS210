/*****************************************************************************
* Project Name: Chada Tech Clocks
* File Name: PROJECT1.cpp
* Author: Ronnie Corpuz
* Course: CS-210 Module 3 Project One
* Date Created: January 25, 2025
* Direction: Develop an object-oriented programming (OOP) application to create
*           two clocks that display simultaneously and allow for user input
*           using secure and efficient C++ code.
* Description: A program that displays both 12-hour and 24-hour format clocks
*              and allows time manipulation through a user menu.
******************************************************************************/

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
using namespace std;

// Forward declarations
void displayClocks(unsigned int h, unsigned int m, unsigned int s);

class Clock {
private:
	unsigned int hour;
	unsigned int minute;
	unsigned int second;

public:
	// Initialize clock to 00:00:00
	Clock() : hour(0), minute(0), second(0) {}

	// Getter functions
	unsigned int getHour() { return hour; }
	unsigned int getMinute() { return minute; }
	unsigned int getSecond() { return second; }

	// Setter functions with display update
	void setHour(unsigned int h) {
		if (h < 24) hour = h;
		displayClocks(hour, minute, second);
	}

	void setMinute(unsigned int m) {
		if (m < 60) minute = m;
		displayClocks(hour, minute, second);
	}

	void setSecond(unsigned int s) {
		if (s < 60) second = s;
		displayClocks(hour, minute, second);
	}

	// Get initial time from user with input validation
	void initializeTime() {
		unsigned int h, m, s;
		do {
			cout << "Enter initial time (24-hour format)\n";
			cout << "Hour (0-23): ";
			cin >> h;
		} while (h >= 24);

		do {
			cout << "Minute (0-59): ";
			cin >> m;
		} while (m >= 60);

		do {
			cout << "Second (0-59): ";
			cin >> s;
		} while (s >= 60);

		hour = h;
		minute = m;
		second = s;
		displayClocks(hour, minute, second);

		// Add a pause for user to see initial time
		cout << "\nPress Enter to continue...";
		cin.ignore();
		cin.get();
	}
};

// Format numbers as two digits
string twoDigitString(unsigned int n) {
	if (n < 10) {
		return "0" + to_string(n);
	}
	return to_string(n);
}

// Create string of n repeated characters
string nCharString(size_t n, char c) {
	return string(n, c);
}

// Format time in 24-hour format (HH:MM:SS)
string formatTime24(unsigned int h, unsigned int m, unsigned int s) {
	return twoDigitString(h) + ":" + twoDigitString(m) + ":" + twoDigitString(s);
}

// Format time in 12-hour format (HH:MM:SS AM/PM)
string formatTime12(unsigned int h, unsigned int m, unsigned int s) {
	unsigned int hour12 = (h == 0 || h == 12) ? 12 : h % 12;
	string ampm = (h < 12) ? " A M" : " P M";
	return twoDigitString(hour12) + ":" + twoDigitString(m) + ":" + twoDigitString(s) + ampm;
}

// Clear screen for clean display
void clearScreen() {
	system("cls");
}

// Display both 12-hour and 24-hour clocks side by side
void displayClocks(unsigned int h, unsigned int m, unsigned int s) {
	clearScreen();
	// Display top border of both clocks
	cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;

	// Display clock headers
	cout << "*" << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << "*" << nCharString(3, ' ');
	cout << "*" << nCharString(6, ' ') << "24-HOUR CLOCK" << nCharString(6, ' ') << "*" << endl;
	cout << endl;

	// Display current time in both formats
	cout << "*" << nCharString(6, ' ') << formatTime12(h, m, s) << nCharString(7, ' ') << "*" << nCharString(3, ' ');
	cout << "*" << nCharString(8, ' ') << formatTime24(h, m, s) << nCharString(9, ' ') << "*" << endl;

	// Display bottom border of both clocks
	cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
}

// Display menu options with formatting
void printMenu(const char* strings[], unsigned int numStrings, unsigned char width) {
	cout << nCharString(width, '*') << endl;

	// Print each menu option
	for (unsigned int i = 0; i < numStrings; i++) {
		cout << "* " << i + 1 << " - " << strings[i];
		// Calculate spacing needed for right alignment
		int spaceNeeded = width - 6 - to_string(i + 1).length() - strlen(strings[i]);
		cout << nCharString(spaceNeeded, ' ') << "*" << endl;

		// Add blank line between options
		if (i < numStrings - 1) {
			cout << endl;
		}
	}

	cout << nCharString(width, '*') << endl;
}

// Get valid menu choice from user (1 to maxChoice)
unsigned int getMenuChoice(unsigned int maxChoice) {
	unsigned int choice;
	do {
		cin >> choice;
	} while (choice < 1 || choice > maxChoice);
	return choice;
}

int main() {
	Clock clock;  // Create clock object
	const char* menuOptions[] = { "Add One Hour", "Add One Minute", "Add One Second", "Exit Program" };

	clock.initializeTime();  // Get initial time from user

	// Main menu loop
	while (true) {
		printMenu(menuOptions, 4, 27);
		unsigned int choice = getMenuChoice(4);

		if (choice == 4) break;  // Exit if user chooses option 4

		switch (choice) {
		case 1:  // Add one hour to the current time
			clock.setHour((clock.getHour() + 1) % 24);  // Increment hour, roll over to 0 if at 23
			break;

		case 2:  // Add one minute to the current time
			if (clock.getMinute() == 59) {    // Handle minute rollover
				clock.setMinute(0);          // Reset minutes to 0
				clock.setHour((clock.getHour() + 1) % 24);  // Increment hour
			}
			else {
				clock.setMinute(clock.getMinute() + 1);     // Increment minute
			}
			break;

		case 3:  // Add one second to the current time
			if (clock.getSecond() == 59) {        // Handle second rollover
				clock.setSecond(0);              // Reset seconds to 0
				if (clock.getMinute() == 59) {    // Handle minute rollover
					clock.setMinute(0);          // Reset minutes to 0
					clock.setHour((clock.getHour() + 1) % 24);  // Increment hour
				}
				else {
					clock.setMinute(clock.getMinute() + 1);     // Increment minute
				}
			}
			else {
				clock.setSecond(clock.getSecond() + 1);        // Increment second
			}
			break;
		}
	}

	return 0;
}