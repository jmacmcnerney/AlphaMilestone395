#include <iostream>
#include <string>
#include <vector>
#include "functions.cpp"

using namespace std;

/*- Player starts in cottage with their grandmother. (DONE, OLD)
- Grandmother has a coin; player has nothing. (DONE, OLD)
- Player cannot leave the cottage without the coin. (DONE, OLD)
- If the player talks to grandmother, she will give him the coin. (DONE, OLD)
- If the player tries to leave the cottage without the coin, grandmother tells him to come talk to her. (DONE, OLD)
- There is a merchant somewhere else outside the cottage. (DONE, OLD)
- The merchant is selling two items. One of them is something grandmother wants, and the other is something she doesn't want. (DONE, OLD)
- They player can buy any item with the coin. (DONE, OLD)
- When the player returns to the cottage with the good item, grandmother is happy. Otherwise she is mad. (DONE, OLD) */

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

	//Items
	Action("CreateItem(Grandmothers coin, Coin)", true);
	Action("CreateItem(Good Apple, Apple)", true);
	Action("CreateItem(Bad Sword, Sword)", true);

	//Icons
	Action("EnableIcon(Open_Door, Open, BobsHouse.Door, Leave the house, true)", true);
	Action("EnableIcon(Open_Door, Open, MerchantFarm.Door, Enter the house, true)", true);
	Action("EnableIcon(Talk_To_Grandmother, Talk, Grandmother, Talk To Grandmother, true)", true);
	Action("EnableIcon(Talk_To_Seller, Talk, Seller, Talk To Seller, true)", true);
	Action("EnableIcon(Take_Coin, Hand, Grandmothers coin, Take the coin, true)", true);
	Action("EnableIcon(Buy_Apple, Coins, Good Apple, Buy the apple, true)", true);
	Action("EnableIcon(Buy_Sword, Coins, Bad Sword, Buy the sword, true)", true);

	//Menu
	Action("ShowMenu()", true);

	//Inventories
	vector<string> playerInv;
	vector<string> grandmotherInv;
	vector<string> sellerInv;
	grandmotherInv.push_back("Grandmothers coin");
	sellerInv.push_back("Good Apple");
	sellerInv.push_back("Bad Sword");

	//Bools
	bool has_coin = false;
	bool has_apple = false;
	bool has_sword = false;

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

		//----------Begin Inventory----------
		else if (i == "input Key Inventory") {
			Action("ClearList()", true);
			for (string item : playerInv) {
				Action("AddToList(" + item + ")", true);
			}
			Action("ShowList(Bob)", true);
		}

		else if (i == "input Close List") {
			Action("HideList()", true);
			Action("ClearList()", true);
			Action("EnableInput()", true);
		}
		//----------End Inventory----------

		//----------Begin Grandmother Dialog----------
		else if (i == "input Talk_To_Grandmother Grandmother") {
			Action("DisableInput()", true);
			Action("WalkTo(Bob, Grandmother)", true);
			Action("ShowDialog()", true);
			Action("ClearDialog()", true);
			Action("SetLeft(Bob)", true);
			Action("SetRight(Grandmother)", true);
			Action("EnableInput()", true);
			if (has_apple)
				Action("SetDialog(Thank you for getting that for me! [end|Of course!])", true);
			else if (has_sword)
				Action("SetDialog(I said buy the APPLE...ugh! [end|oops...])", true);
			else
				Action("SetDialog(Take this coin and buy me an APPLE from the merchant! [take|Ok grandma.])", true);
		}

		else if (i == "input Selected take") {
			Action("HideDialog()", true);
			for (string item : grandmotherInv) {
				Action("AddToList(" + item + ")", true);
			}
			Action("ShowList(Grandmother)", true);
		}
		//----------End Grandmother Dialog----------

		//----------Begin Seller Dialog----------
		else if (i == "input Talk_To_Seller Seller") {
			Action("DisableInput()", true);
			Action("WalkTo(Bob, Seller)", true);
			Action("ShowDialog()", true);
			Action("ClearDialog()", true);
			Action("SetLeft(Bob)", true);
			Action("SetRight(Seller)", true);
			Action("EnableInput()", true);
			if (has_coin)
				Action("SetDialog(Check out what I have for sale! [buy|Let me see!] [end|No thanks.])", true);
			else
				Action("SetDialog(Seller has wares if you have coin. [end|(Leave)])", true);
		}

		else if (i == "input Selected buy") {
			Action("HideDialog()", true);
			for (string item : sellerInv) {
				Action("AddToList(" + item + ")", true);
			}
			Action("ShowList(Seller)", true);
		}

		else if (i == "input Selected end") {
			Action("HideDialog()", true);
		}
		//----------End Seller Dialog----------

		//----------Begin Travel----------
		else if (i == "input Open_Door BobsHouse.Door") {
			if (has_coin) {
				Action("Exit(Bob, BobsHouse.Door, true)", true);
				Action("Enter(Bob, MerchantFarm.Door, true)", true);
			}
			else {
				Action("DisableInput()", true);
				Action("WalkTo(Bob, BobsHouse.Door)", true);
				Action("ShowDialog()", true);
				Action("ClearDialog()", true);
				Action("SetLeft(Bob)", true);
				Action("SetRight(Grandmother)", true);
				Action("EnableInput()", true);
				if (has_apple)
					Action("SetDialog(Dont leave! Dinner will be ready soon. [end|Yum!])", true);
				else if (has_sword)
					Action("SetDialog(NO LEAVING! You are grounded! [end|Aw. No fair.])", true);
				else
					Action("SetDialog(Do not leave the house without coming to talk to me! [end|Be right there.])", true);
			}
		}

		else if (i == "input Open_Door MerchantFarm.Door") {
			Action("Exit(Bob, MerchantFarm.Door, true)", true);
			Action("Enter(Bob, BobsHouse.Door, true)", true);
		}
		//----------End Travel----------

		//----------Begin Item Transactions----------
		else if (i == "input Take_Coin Grandmothers coin") {
			Action("RemoveFromList(Grandmothers coin)", true);
			for (int i = 0; i < grandmotherInv.size(); i++) {
				if (grandmotherInv[i] == "Grandmothers coin") {
					grandmotherInv.erase(grandmotherInv.begin() + i);
				}
			}
			Action("DisableIcon(Take_Coin, Grandmothers coin)", true);
			playerInv.push_back("Grandmothers coin");
			has_coin = true;
		}

		else if (i == "input Buy_Apple Good Apple") {
			Action("RemoveFromList(Good Apple)", true);
			for (int i = 0; i < sellerInv.size(); i++) {
				if (sellerInv[i] == "Good Apple") {
					sellerInv.erase(sellerInv.begin() + i);
				}
			}
			Action("DisableIcon(Buy_Apple, Good Apple)", true);
			playerInv.erase(playerInv.begin());
			playerInv.push_back("Good Apple");
			Action("HideList()", true);
			has_apple = true;
			has_coin = false;
		}

		else if (i == "input Buy_Sword Bad Sword") {
			Action("RemoveFromList(Bad Sword)", true);
			for (int i = 0; i < sellerInv.size(); i++) {
				if (sellerInv[i] == "Bad Sword") {
					sellerInv.erase(sellerInv.begin() + i);
				}
			}
			Action("DisableIcon(Buy_Sword, Bad Sword)", true);
			playerInv.erase(playerInv.begin());
			playerInv.push_back("Bad Sword");
			Action("HideList()", true);
			has_sword = true;
			has_coin = false;
		}
		//----------End Item Transactions----------
	}

	return 0;
}