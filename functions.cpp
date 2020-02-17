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
	//string actionString = "";

	//actionString = "CreateCharacter(" + name + ", " + bodyType + ")";
	Action("CreateCharacter(" + name + ", " + bodyType + ")", true);

	if (clothing != "") {
		//actionString = "SetClothing(" + name + ", " + clothing + ")";
		//Action(actionString, true);
		Action("SetClothing(" + name + ", " + clothing + ")", true);
	}
	if (hairStyle != "") {
		//actionString = "SetHairStyle(" + name + ", " + hairStyle + ")";
		Action("SetHairStyle(" + name + ", " + hairStyle + ")", true);
	}
	if (hairColor != "") {
		//actionString = "SetHairColor(" + name + ", " + hairColor + ")";
		Action("SetHairColor(" + name + ", " + hairColor + ")", true);
	}
	if (position != "") {
		//actionString = "SetPosition(" + name + ", " + position + ")";
		Action("SetPosition(" + name + ", " + position + ")", true);
	}
}

//Icon Setup
void SetupIcons(vector<string> titles, vector<string> icons, vector<string> objects, vector<string> descriptions, vector<string> defaults) {
	
	int vectorSize = titles.size();
	int sentinal = 0;
	//string actionString = "";

	while (sentinal < vectorSize) {
		//actionString = "EnableIcon(" + titles[sentinal] + ", " + icons[sentinal] + ", " + objects[sentinal] + ", " + descriptions[sentinal] + ", " + defaults[sentinal] + ")";
		Action("EnableIcon(" + titles[sentinal] + ", " + icons[sentinal] + ", " + objects[sentinal] + ", " + descriptions[sentinal] + ", " + defaults[sentinal] + ")", true);
		sentinal++;
	}

	//Action("EnableIcon(Open_Door, Open, BobsHouse.Door, Leave the house, true)", true);
}

void SetupDialog(string mainChar, string talkingTo) {
	string actionString = "";

	Action("DisableInput()", true);

	//actionString = "WalkTo(" + mainChar + ", " + talkingTo + ")";
	Action("WalkTo(" + mainChar + ", " + talkingTo + ")", true);
	Action("ShowDialog()", true);
	Action("ClearDialog()", true);

	//actionString = "SetLeft(" + mainChar + ")";
	Action("SetLeft(" + mainChar + ")", true);
	//Action("SetLeft(Bob)", true);

	//actionString = "SetRight(" + mainChar + ")";
	Action("SetRight(" + talkingTo + ")", true);
	//Action("SetRight(Grandmother)", true);
	Action("EnableInput()", true);
}

void PurchaseFunct(string purchase, string input, vector<string> & storeInv, vector<string> & inventory, bool & coin, bool & purchaseCheck) {
	
//	else if (i == "input Buy_Sword " + purchase) {
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