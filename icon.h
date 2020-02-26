#ifndef ICON_H
#define ICON_H
#include <string>
using namespace std;

class Icon {
public:
	Icon(); // constructor
	//~Icon(); // destructor
	Icon(string title, string image, string object, string description, string isDefault);

	// set functions
	void setTitle(string newTitle);
	void setImage(string newImage);
	void setObject(string newObject);
	void setDescription(string newDescription);
	void setDefault(bool newIsDefault);

	// get functions
	string getTitle();
	string getImage();
	string getObject();
	string getDescription();
	string getIsDefault();

private:
	// Properties of the icon, stored as strings to be usable with Camelot
	string title; // the name of the icon
	string image; // indicates which Camelot icon to be displayed
	string object; // the object the icon belongs to
	string description; // a short description of the action associated with the icon
	string isDefault; // either true or false; indicates whether this is the default interaction
};
#endif