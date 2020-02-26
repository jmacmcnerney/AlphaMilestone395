//#include "icon.h"
//#include <vector>
#ifndef CHAPTER1_H
#define CHAPTER1_H
#include "icon.h"
#include <vector>
class Chapter1 {
public:
	Chapter1();
	~Chapter1();
	bool runSetup(); // runs setup for chapter 1. returns true if setup was successful.
	void run(); // runs the chapter

	vector<Icon> icons;

	vector<string> playerInv;
	vector<string> grandmotherInv;
	vector<string> sellerInv;

	bool has_coin;
	bool has_apple;
	bool has_sword;
	vector<bool> checks;
	string modified_I;
};
#endif