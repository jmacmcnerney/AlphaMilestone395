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
	
	Action("CreateCharacter(" + name + ", " + bodyType + ")", true);

	if (clothing != "") {
		Action("SetClothing(" + name + ", " + clothing + ")", true);
	}
	if (hairStyle != "") {
		Action("SetHairStyle(" + name + ", " + hairStyle + ")", true);
	}
	if (hairColor != "") {
		Action("SetHairColor(" + name + ", " + hairColor + ")", true);
	}
	if (position != "") {
		Action("SetPosition(" + name + ", " + position + ")", true);
	}
}

//Icon Setup
void SetupIcons(vector<string> titles, vector<string> icons, vector<string> objects, vector<string> descriptions, vector<string> defaults) {
	
	int vectorSize = titles.size();
	int sentinal = 0;

	while (sentinal < vectorSize) {
		Action("EnableIcon(" + titles[sentinal] + ", " + icons[sentinal] + ", " + objects[sentinal] + ", " + descriptions[sentinal] + ", " + defaults[sentinal] + ")", true);
		sentinal++;
	}

}

//Does the inital setup for Dialog
void SetupDialog(string mainChar, string talkingTo) {
	string actionString = "";

	Action("DisableInput()", true);

	Action("WalkTo(" + mainChar + ", " + talkingTo + ")", true);
	Action("ShowDialog()", true);
	Action("ClearDialog()", true);

	Action("SetLeft(" + mainChar + ")", true);

	Action("SetRight(" + talkingTo + ")", true);
	Action("EnableInput()", true);
}

//Handles all of purchasing something for a coin
void PurchaseFunct(string purchase, string input, vector<string> & storeInv, vector<string> & inventory, bool & coin, bool & purchaseCheck) {
	
	Action("RemoveFromList(" + purchase + ")", true);
	for (int i = 0; i < storeInv.size(); i++) {
		if (storeInv[i] == purchase) {
			storeInv.erase(storeInv.begin() + i);
		}
	}
	Action("DisableIcon(" + input + ", " + purchase + ")", true);
	inventory.erase(inventory.begin());
	inventory.push_back(purchase);
	Action("HideList()", true);

	coin = false;
	purchaseCheck = true;
}

//Splits the input into one of its words. NumToSkip is to skip to the start of the word you want, Reverse is to start 
//at the end of the string
string splitInput(string input, int numToSkip, bool reverse) {
	string output = "";

	//For going forwards
	if (!reverse) {
		for (int i = 0 + numToSkip; i < input.size(); i++) {
			if (input[i] == ' ') {
				i = input.size();
			}
			if (i != input.size()) {
				output = output + input[i];
			}
		}
	}

	//For going backwards
	else {
		for (int i = input.size()-1; i > 0; i--) {
			if (input[i] == ' ') {
				i = 0;
			}
			if (i != 0) {
				output = input[i] + output;
			}
		}
	}

	return output;
}