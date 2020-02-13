#include <iostream>
#include <string>
#include <vector>
#include "functions.cpp"

using namespace std;

/*- Player starts in cottage with their grandmother. (DONE, OLD)
- Grandmother has a coin; player has nothing. 
- Player cannot leave the cottage without the coin. (DONE, OLD)
- If the player talks to grandmother, she will give him the coin. (DONE, OLD)
- If the player tries to leave the cottage without the coin, grandmother tells him to come talk to her. (DONE, OLD)
- There is a merchant somewhere else outside the cottage. (DONE, OLD)
- The merchant is selling two items. One of them is something grandmother wants, and the other is something she doesn't want.
- They player can buy any item with the coin.
- When the player returns to the cottage with the good item, grandmother is happy. Otherwise she is mad.*/

int main() {
	//Place Creations
	Action("CreatePlace(BobsHouse, Cottage)", true);
	Action("CreatePlace(MerchantFarm, Farm)", true);

	//Bob Character
	Action("CreateCharacter(Bob, B)", true);
	Action("SetClothing(Bob, Peasant)", true);
	Action("SetHairStyle(Bob, Short_Full)", true);
	Action("SetPosition(Bob, BobsHouse.Door)", true);

	//Grandmother Character
	Action("CreateCharacter(Grandmother, A)", true);
	Action("SetClothing(Grandmother, Beggar)", true);
	Action("SetHairStyle(Grandmother, Ponytail)", true);
	Action("SetHairColor(Grandmother, Gray)", true);
	Action("SetPosition(Grandmother, BobsHouse.Bookshelf)", true);

	//Seller Character
	Action("CreateCharacter(Seller, B)", true);
	Action("SetClothing(Seller, Merchant)", true);
	Action("SetHairStyle(Seller, Spiky)", true);
	Action("SetPosition(Seller, MerchantFarm.Anvil)", true);

	//Icons
	Action("EnableIcon(Open_Door, Open, BobsHouse.Door, Leave the house, true)", true);
	Action("EnableIcon(Open_Door, Open, MerchantFarm.Door, Enter the house, true)", true);
	Action("EnableIcon(Talk_To_Grandmother, Talk, Grandmother, Talk To Grandmother, true)", true);
	Action("EnableIcon(Talk_To_Seller, Talk, Seller, Talk To Seller, true)", true);

	//Menu
	Action("ShowMenu()", true);

	//Inventories
	vector<string> playerInv;
	vector<string> chestInv;

	//Bools
	bool has_coin = false;

	// Respond to input.
	while (true) {
		//----------Begin Setup----------
		string i;
		getline(cin, i);
		if (i == "input Selected Start") {
			Action("SetCameraFocus(Bob)", true);
			Action("HideMenu()", true);
			Action("EnableInput()", true);
		}
		//----------End Setup----------

		//----------Begin Grandmother Dialog----------
		else if (i == "input Talk_To_Grandmother Grandmother") {
			Action("WalkTo(Bob, Grandmother)", true);
			Action("ShowDialog()", true);
			Action("ClearDialog()", true);
			Action("SetLeft(Bob)", true);
			Action("SetRight(Grandmother)", true);
			Action("SetDialog(Take this coin and buy me an APPLE from the merchant! [ok|Ok grandma.])", true);
		}

		else if (i == "input Selected ok") {
			Action("HideDialog()", true);
			has_coin = true;
		}

		else if (i == "input Selected be right there") {
			Action("HideDialog()", true);
		}
		//----------End Grandmother Dialog----------

		//----------Begin Travel----------
		else if (i == "input Open_Door BobsHouse.Door") {
			if (has_coin) {
				Action("Exit(Bob, BobsHouse.Door, true)", true);
				Action("Enter(Bob, MerchantFarm.Door, true)", true);
			}
			else {
				Action("ShowDialog()", true);
				Action("ClearDialog()", true);
				Action("SetLeft(Bob)", true);
				Action("SetRight(Grandmother)", true);
				Action("SetDialog(Do not leave the house without coming to talk to me! [be right there|Be right there.])", true);
			}
		}

		else if (i == "input Open_Door MerchantFarm.Door") {
			Action("Exit(Bob, MerchantFarm.Door, true)", true);
			Action("Enter(Bob, BobsHouse.Door, true)", true);
		}
		//----------End Travel----------
	}

	return 0;
}