/* 
|| A number of functions for simplifying actions in Camelot. 
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Wait for given input before continueing
void WaitFor(string message) {
	while (true) {
		string i;
		getline(cin, i);
		if (i == message) {
			break;
		}
	}
}

// Send a command to Camelot.
void Action(string command, bool waitUntilSuccess) {
	cout << ("start " + command) << endl;
	if (waitUntilSuccess) {
		WaitFor("succeeded " + command);
	}
}

//Character Creation Function
void SetupCharacter(string name, string bodyType, string clothing, string hairStyle, string hairColor, string position) {
	string actionString = "";

	actionString = "CreateCharacter(" + name + ", " + bodyType + ")";
	Action(actionString, true);

	if (clothing != "") {
		actionString = "SetClothing(" + name + ", " + clothing + ")";
		Action(actionString, true);
	}
	if (hairStyle != "") {
		actionString = "SetHairStyle(" + name + ", " + hairStyle + ")";
		Action(actionString, true);
	}
	if (hairColor != "") {
		actionString = "SetHairColor(" + name + ", " + hairColor + ")";
		Action(actionString, true);
	}
	if (position != "") {
		actionString = "SetPosition(" + name + ", " + position + ")";
		Action(actionString, true);
	}
}

//Icon Setup
void SetupIcons(vector<string> titles, vector<string> icons, vector<string> objects, vector<string> descriptions, vector<string> defaults) {
	
	int vectorSize = titles.size();
	int sentinal = 0;
	string actionString = "";

	while (sentinal < vectorSize) {
		actionString = "EnableIcon(" + titles[sentinal] + ", " + icons[sentinal] + ", " + objects[sentinal] + ", " + descriptions[sentinal] + ", " + defaults[sentinal] + ")";
		Action(actionString, true);
		sentinal++;
	}

	//Action("EnableIcon(Open_Door, Open, BobsHouse.Door, Leave the house, true)", true);
}