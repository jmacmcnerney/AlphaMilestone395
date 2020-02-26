#include <iostream>
#include <string>
#include "functions.cpp"
#include "chapter1.h"

using namespace std;

Chapter1::Chapter1() {

}
Chapter1::~Chapter1() {
	while (icons.size() > 0) {
		icons.pop_back();
	}
}
bool Chapter1::runSetup() {
	//---------- CHAPTER 1 SETUP ----------

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
	icons.push_back(Icon("Open Door", "Open", "BobsHouse.Door", "Leave the house", "true"));
	icons.push_back(Icon("Open Door", "Open", "MerchantFarm.Door", "Enter the house", "true"));
	icons.push_back(Icon("Talk to Grandmother", "Talk", "Grandmother", "Talk to Grandmother", "true"));
	icons.push_back(Icon("Talk to Seller", "Talk", "Seller", "Talk to Seller", "true"));
	icons.push_back(Icon("Take Coin", "Hand", "Grandmothers_coin", "Take the coin", "true"));
	icons.push_back(Icon("Buy Apple", "Coins", "Good_Apple", "Buy the apple", "true"));
	icons.push_back(Icon("Buy Sword", "Coins", "Bad_Sword", "Buy the sword", "true"));
	SetupIcons(icons);

	//Menu
	Action("ShowMenu()", true);

	//Inventories
	grandmotherInv.push_back("Grandmothers_coin");
	sellerInv.push_back("Good_Apple");
	sellerInv.push_back("Bad_Sword");

	//Bools
	has_coin = false;
	has_apple = false;
	has_sword = false;
	checks = { has_coin, has_apple, has_sword };
	modified_I = "";

	return true;

	//---------- END SETUP ----------
}
void Chapter1::run() {
	while (true) {
		string i;
		getline(cin, i);

		//Gets the first word that isn't "input"
		modified_I = splitInput(i, 6, false);

		//If it's under the "Selected" keyword
		if (modified_I == "Selected") {

			modified_I = splitInput(i, 0, true);

			if (modified_I == "Start") {
				StartOption("Bob");

			}
			else if (modified_I == "take") {
				ShowInv("Grandmother", grandmotherInv);
			}
			else if (modified_I == "buy") {
				ShowInv("Seller", sellerInv);
			}

			else if (modified_I == "end") {
				Action("HideDialog()", true);
			}
			else if (modified_I == "Resume") {
				Action("HideMenu()", true);
				Action("EnableInput()", true);
			}
			else if (modified_I == "Quit") {
				Action("Quit()", true);
			}
		}

		//If it's under the "Key" keyword
		else if (modified_I == "Key") {

			modified_I = splitInput(i, 0, true);
			if (modified_I == "Inventory") {
				Action("ClearList()", true);
				for (string item : playerInv) {
					Action("AddToList(" + item + ")", true);
				}
				Action("ShowList(Bob)", true);
			}
			else if (modified_I == "Pause") {
				Action("DisableInput()", true);
				Action("ShowMenu()", true);
			}
		}

		//If it's under the "Close" keyword
		else if (modified_I == "Close") {
			CloseList();
		}

		//If it's under the "Talk" keyword
		else if (modified_I == "Talk") {
			modified_I = splitInput(i, 0, true);

			//Grandmother's dialog
			if (modified_I == "Grandmother") {
				SetupDialog("Bob", "Grandmother", true);
				if (has_apple)
					Action("SetDialog(Thank you for getting that for me! [end|Of course!])", true);
				else if (has_sword)
					Action("SetDialog(I said buy the APPLE...ugh! [end|oops...])", true);
				else
					Action("SetDialog(Take this coin and buy me an APPLE from the merchant! [take|Ok grandma.])", true);
			}
			//Seller's dialog
			else if (modified_I == "Seller") {
				SetupDialog("Bob", "Seller", true);
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
						Transition("Bob", "BobsHouse.Door", "MerchantFarm.Door");

					}
					else {
						SetupDialog("Bob", "Grandmother", false);
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
					Transition("Bob", "MerchantFarm.Door", "BobsHouse.Door");

				}

			}

		}

		//If it's under the "Take" keyword
		else if (modified_I == "Take") {
			Grab("Grandmothers_coin", "Take Coin", grandmotherInv, playerInv, has_coin, has_coin, false);
			has_coin = true;
		}

		else if (modified_I == "Buy") {
			modified_I = splitInput(i, 0, true);
			//Buying the Apple
			if (modified_I == "Good_Apple") {
				Grab("Good_Apple", "Buy Apple", sellerInv, playerInv, has_coin, has_apple, true);
			}
			//Buying the Sword
			else if (modified_I == "Bad_Sword") {
				Grab("Bad_Sword", "Buy Sword", sellerInv, playerInv, has_coin, has_sword, true);
			}
		}
	}
}