#include <iostream>
#include <string>
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
	SetupCharacter("Bob", "B", "Peasant", "Short_Full", "", "BobsHouse.Door");

	//Grandmother Character
	SetupCharacter("Grandmother", "A", "Beggar", "Ponytail", "Gray", "BobsHouse.Bookshelf");

	//Seller Character
	SetupCharacter("Seller", "B", "Merchant", "Spiky", "", "MerchantFarm.Anvil");

	//Items
	Action("CreateItem(Grandmothers_coin, Coin)", true);
	Action("CreateItem(Good_Apple, Apple)", true);
	Action("CreateItem(Bad_Sword, Sword)", true);

	//Icons
	vector<string> titles{"Open Door", "Open Door", "Talk To Grandmother", "Talk To Seller", "Take Coin", "Buy Apple", "Buy Sword"};
	vector<string> icons{"Open", "Open", "Talk", "Talk", "Hand", "Coins", "Coins"};
	vector<string> objects{"BobsHouse.Door", "MerchantFarm.Door", "Grandmother", "Seller", "Grandmothers_coin", "Good_Apple", "Bad_Sword"};
	vector<string> descriptions{"Leave the house", "Enter the house", "Talk To Grandmother", "Talk To Seller", "Take the coin", "Buy the apple", "Buy the sword"};
	vector<string> defaults{"true", "true", "true", "true", "true", "true", "true",};



	SetupIcons(titles, icons, objects, descriptions, defaults);

	//Menu
	Action("ShowMenu()", true);

	//Inventories
	vector<string> playerInv;
	vector<string> grandmotherInv;
	vector<string> sellerInv;
	grandmotherInv.push_back("Grandmothers_coin");
	sellerInv.push_back("Good_Apple");
	sellerInv.push_back("Bad_Sword");

	//Bools
	bool has_coin = false;
	bool has_apple = false;
	bool has_sword = false;
	string modified_I = "";

	// Respond to input.
	while (true) {
		//----------Begin Setup----------
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = splitInput(i, 6, false);

		//If it's under the "Selected" keyword
		if (modified_I == "Selected") {

			modified_I = splitInput(i, 0, true);

			if (modified_I == "Start") {
				Action("SetCameraFocus(Bob)", true);
				Action("HideMenu()", true);
				Action("EnableInput()", true);
			}
			else if (modified_I == "take") {
				Action("HideDialog()", true);
				for (string item : grandmotherInv) {
					Action("AddToList(" + item + ")", true);
				}
				Action("ShowList(Grandmother)", true);
			}
			else if (modified_I == "buy") {
				Action("HideDialog()", true);
				for (string item : sellerInv) {
					Action("AddToList(" + item + ")", true);
				}
				Action("ShowList(Seller)", true);
			}

			else if (modified_I == "end") {
				Action("HideDialog()", true);
			}
		}
		
		//If it's under the "Key" keyword
		else if (modified_I == "Key") {
			Action("ClearList()", true);
			for (string item : playerInv) {
				Action("AddToList(" + item + ")", true);
			}
			Action("ShowList(Bob)", true);
		}
		
		//If it's under the "Close" keyword
		else if (modified_I == "Close") {
			Action("HideList()", true);
			Action("ClearList()", true);
			Action("EnableInput()", true);
		}
		
		//If it's under the "Talk" keyword
		else if (modified_I == "Talk") {
			modified_I = splitInput(i, 0, true);

			//Grandmother's dialog
			if (modified_I == "Grandmother") {
				SetupDialog("Bob", "Grandmother");
				if (has_apple)
					Action("SetDialog(Thank you for getting that for me! [end|Of course!])", true);
				else if (has_sword)
					Action("SetDialog(I said buy the APPLE...ugh! [end|oops...])", true);
				else
					Action("SetDialog(Take this coin and buy me an APPLE from the merchant! [take|Ok grandma.])", true);
			}
			//Seller's dialog
			else if (modified_I == "Seller") {
				SetupDialog("Bob", "Seller");
				if (has_coin)
					Action("SetDialog(Check out what I have for sale! [buy|Let me see!] [end|No thanks.])", true);
				else
					Action("SetDialog(Seller has wares if you have coin. [end|(Leave)])", true);
			}
		}
		
		//If it's under the "Open" keyword
		else if (modified_I == "Open") {
			modified_I = splitInput(i, 11, false);

			if (modified_I == "Door") {
				modified_I = splitInput(i, 0, true);

				//Going outside
				if (modified_I == "BobsHouse.Door") {
					if (has_coin) {
						Action("Exit(Bob, BobsHouse.Door, true)", true);
						Action("Enter(Bob, MerchantFarm.Door, true)", true);
					}
					else {
						SetupDialog("Bob", "Grandmother");
						if (has_apple)
							Action("SetDialog(Dont leave! Dinner will be ready soon. [end|Yum!])", true);
						else if (has_sword)
							Action("SetDialog(NO LEAVING! You are grounded! [end|Aw. No fair.])", true);
						else
							Action("SetDialog(Do not leave the house without coming to talk to me! [end|Be right there.])", true);
					}
				}

				//Going inside
				else if (modified_I == "MerchantFarm.Door") {
					Action("Exit(Bob, MerchantFarm.Door, true)", true);
					Action("Enter(Bob, BobsHouse.Door, true)", true);
				}

			}

		}

		//If it's under the "Take" keyword
		else if (modified_I == "Take") {
			Action("RemoveFromList(Grandmothers_coin)", true);
			for (int i = 0; i < grandmotherInv.size(); i++) {
				if (grandmotherInv[i] == "Grandmothers_coin") {
					grandmotherInv.erase(grandmotherInv.begin() + i);
				}
			}
			Action("DisableIcon(Take Coin, Grandmothers_coin)", true);
			playerInv.push_back("Grandmothers_coin");
			has_coin = true;
		}

		else if (modified_I == "Buy") {
			modified_I = splitInput(i, 0, true);

			//Buying the Apple
			if (modified_I == "Good_Apple") {
				PurchaseFunct("Good_Apple", "Buy Apple", sellerInv, playerInv, has_coin, has_apple);
			}
			//Buying the Sword
			else if (modified_I == "Bad_Sword") {
				PurchaseFunct("Bad_Sword", "Buy Sword", sellerInv, playerInv, has_coin, has_sword);
			}
		}

	}

	return 0;
}