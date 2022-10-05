/*
 * ClockProject1.cpp
 *
 *  Date: 9/13/2022
 *  Author: Caleb Jones
 */

#include <iostream>
#include <ctype.h>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Time {
private:
	
	int seconds;
	int minutes;
	int hour;

public:
	void setSeconds(int sec) {
		seconds = sec;
	}
	int getSeconds() {
		return seconds;
	}
	void setMinutes(int min) {
		minutes = min;
	}
	int getMinutes() {
		return minutes;
	}
	void setHours(int hr) {
		hour = hr;
	}
	int getHours() {
		return hour;
	}

	void addSecond() {
		int sec = getSeconds();

		sec += 1;//The goal of the function

		//Qualifiers to maintain that time does not exceed its bounds
		if (sec > 59) {
			addMinute();

			if (sec == 60) {
				sec = 0;
			}
			else {
				sec = sec - 60;
			}
		}
		setSeconds(sec);
	}

	void addMinute() {
		int min = getMinutes();

		min += 1;//The goal of the function

		//Qualifiers to maintain that time does not exceed its bounds
		if (min > 59) {
			addHour();

			if (min == 60) {
				min = 0;
			}
			else {
				min = min - 60;
			}
		}
		setMinutes(min);
	}

	void addHour() {
		int hr = getHours();

		hr += 1;//The goal of the function

		//Qualifiers to maintain that time does not exceed its bounds
		if (hr > 23) {
			hr = 0;
		}
		setHours(hr);
	}
};

//Converts each numerical digit as a 2 digit string
string twoDigitString(int num) {
	string time = "";

	if (num < 10) {
		time.append("0");
	}
	time.append(to_string(num));

	return time;
}

string printCharBar(int len, char a) {
	string bar = "";

	//Builds a bar of '*'s for a given length
	for (int i = 0; i < len; i++) {
		bar += a;
	}

	return bar;
}

//Builds the 24 hour clock format based on the hours, minutes and seconds
string set24Hours(int hr, int min, int sec) {
	string clock24 = "";
	
	//Convert time ints into a string to build time:
	string hrStr = twoDigitString(hr);
	string minStr = twoDigitString(min);
	string secStr = twoDigitString(sec);

	//Build the clock string:
	clock24.append(hrStr);
	clock24.append(":");
	clock24.append(minStr);
	clock24.append(":");
	clock24.append(secStr);

	return clock24;
}

//Builds the 12 hour clock format based on the hours, minutes and seconds
string set12Hours(int hr, int min, int sec) {
	string clock12 = "";
	string meridiem = "";//For a.m or p.m

	//Determine if time is A.M or P.M
	if (hr > 11) {
		meridiem = " P M";

		//Updates the hour count if it is greater than 12
		if (hr > 12) {
			hr = hr - 12;
		}
	}
	else {
		meridiem = " A M";
	}

	//Catches midnight case
	if (hr == 0) {
		hr = 12;
	}

	//Convert time ints into a string to build time:
	string hrStr = twoDigitString(hr);
	string minStr = twoDigitString(min);
	string secStr = twoDigitString(sec);

	//Build the clock string:
	clock12.append(hrStr);
	clock12.append(":");
	clock12.append(minStr);
	clock12.append(":");
	clock12.append(secStr);
	clock12.append(meridiem);

	return clock12;
}

void printMenu() {
	string display = "* 1 - Add One Hour        *";

	cout << printCharBar(display.length(), '*') << endl;
	cout << display << endl << endl;
	cout << "* 2 - Add One Minute      *" << endl << endl;
	cout << "* 3 - Add One Second      *" << endl << endl;
	cout << "* 4 - Exit Program        *" << endl;
	cout << printCharBar(display.length(), '*') << endl;
}

void displayClock(int hr, int min, int sec) {
	string display12 = "*     12-Hour  Clock     *";
	string display24 = "*     24-Hour Clock     *";
	string mainClock12 = set12Hours(hr, min, sec);
	string mainClock24 = set24Hours(hr, min, sec);
	/*
	cout << endl << printCharBar(display12.length(), '*') << "     " << printCharBar(display24.length(), '*') << endl;
	cout << display12 << "     " << display24 << endl;
	cout << "*      " << mainClock12 << "      *" << "     " << "*       " << mainClock24 << "        *" << endl;
	cout << printCharBar(display12.length(), '*') << "     " << printCharBar(display24.length(), '*') << endl << endl;
	*/

	cout << printCharBar(27, '*') << printCharBar(3, ' ') << printCharBar(27, '*') << endl;
	cout << "*" << printCharBar(6, ' ') << "12-HOUR CLOCK" << printCharBar(6, ' ') << "*" << printCharBar(3, ' ');
	cout << "*" << printCharBar(6, ' ') << "24-HOUR CLOCK" << printCharBar(6, ' ') << "*" << endl << endl;
	cout << "*" << printCharBar(6, ' ') << mainClock12 << printCharBar(7, ' ') << "*" << printCharBar(3, ' ');
	cout << "*" << printCharBar(8, ' ') << mainClock24 << printCharBar(9, ' ') << "*" << endl;
	cout << printCharBar(27, '*') << printCharBar(3, ' ') << printCharBar(27, '*') << endl;
}

int menuInput() {
	string userInput = "";
	bool validInput = false;
	int choice = -1;

	cin >> userInput;

	//Ensure user inputted valid menu option
	while (validInput == false) {

		//Validate it was an integer
		for (int i = 0; i < userInput.length(); i++) {
			if (isdigit(userInput[i])) {
				validInput = true;
			}
			else {
				validInput = false;
				break;
			}
		}
		if (validInput == false) {
			cin >> userInput;
			continue;
		}
		//Convert number string into integer and validate 1 thru 4
		else {
			choice = stoi(userInput);
			if ((choice < 1) || (choice > 4)) {
				cin >> userInput;
				validInput = false;
				continue;
			}
		}
	}
	return choice;
}
int main()
{
	Time time;
	int choice = -1;

	//Temp values to display time at the start of the program
	time.setHours(23);
	time.setMinutes(2);
	time.setSeconds(59);


	//Loop through menu options until user exits
	while (choice != 4) {

		//Flowchart display requirements
		system("cls");//Clear the screen
		displayClock(time.getHours(), time.getMinutes(), time.getSeconds());
		printMenu();
		choice = menuInput();

		//Linking the input to the menu options
		if (choice == 1) {//Add one hour
			time.addHour();
		}
		else if (choice == 2) {//Add one minute
			time.addMinute();
		}
		else if (choice == 3) {//Add one second
			time.addSecond();
		}
		else if (choice == 4) {//Exit program
			exit(0);
		}
	}
	return 0;
}






