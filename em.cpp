#include <iostream>
#include <string>
#include <vector>
#include "functions.cpp"

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

int main() {
	//Place Creations
	Action("CreatePlace(BobsHouse, Cottage)", true);
	Action("CreatePlace(Newcity, City)", true);
	
	//Bob Character
	Action("CreateCharacter(Bob, B)", true);
	Action("SetClothing(Bob, Peasant)", true);
	Action("SetHairStyle(Bob, Short_Full)", true);
	Action("SetPosition(Bob, BobsHouse.Door)", true);

	Action("CreateCharacter(Grandmother, A)", true);
	Action("SetClothing(Grandmother, Beggar)", true);
	Action("SetHairStyle(Grandmother, Ponytail)", true);
	Action("SetPosition(Grandmother, BobsHouse.Door", true);

	Action("CreateCharacter(Seller, B)", true);
	Action("SetClothing(Seller, Merchant)", true);
	Action("SetHairStyle(Seller, Spiky)", true);

	//Menu
	Action("ShowMenu()", true);
	//Inventories
	vector<string> playerInv;
	vector<string> chestInv;

	// Respond to input.
	while (true) {
		string i;
		getline(cin, i);
		if (i == "input Selected Start") {
			Action("SetCameraFocus(Bob)", true);
			Action("HideMenu()", true);
			Action("EnableInput()", true);
		}
	}

	return 0;
}