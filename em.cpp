#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*- Player starts in cottage with their grandmother.
- Grandmother has a coin; player has nothing.
- Player cannot leave the cottage without the coin.
- If the player talks to grandmother, she will give him the coin.
- If the player tries to leave the cottage without the coin, grandmother tells him to come talk to her.
- There is a merchant somewhere else outside the cottage.
- The merchant is selling two items. One of them is something grandmother wants, and the other is something she doesn't want.
- They player can buy any item with the coin.
- When the player returns to the cottage with the good item, grandmother is happy. Otherwise she is mad.*/

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
void Action(string command) {
	cout << ("start " + command) << endl;
	WaitFor("succeeded " + command);
}

int main() {
	//Place Creations
	Action("CreatePlace(BobsHouse, Cottage)");
	Action("CreatePlace(Prison, Dungeon)");
	Action("CreatePlace(Newcity, City)");
	//Bob Character
	Action("CreateCharacter(Bob, B)");
	Action("SetClothing(Bob, Peasant)");
	Action("SetHairStyle(Bob, Short_Full)");
	Action("SetPosition(Bob, BobsHouse.Door)");
	//Menu
	Action("ShowMenu()");
	//Inventories
	vector<string> playerInv;
	vector<string> chestInv;

	// Respond to input.
	while (true) {
		string i;
		getline(cin, i);
		if (i == "input Selected Start") {
			Action("SetCameraFocus(Bob)");
			Action("HideMenu()");
			Action("EnableInput()");
		}
	}

	return 0;
}