#include "icon.h"
using namespace std;

Icon::Icon() {
	this->title = "";
	this->image = "";
	this->object = "";
	this->description = "";
	this->isDefault = "";
}

/*
Icon::~Icon() {
	delete title;
	delete this->image;
	delete this->object;
	delete this->description;
	delete this->isDefault;
}
*/

Icon::Icon(string title, string image, string object, string description, string isDefault) {
	this->title = title;
	this->image = image;
	this->object = object;
	this->description = description;
	this->isDefault = isDefault;
}

//----------GET FUNCTIONS----------
void Icon::setTitle(string newTitle) {
	this->title = newTitle;
}
void Icon::setImage(string newImage) {
	this->image = newImage;
}
void Icon::setObject(string newObject) {
	this->object = newObject;
}
void Icon::setDescription(string newDescription) {
	this->description = newDescription;
}
void Icon::setDefault(bool newIsDefault) {
	if (newIsDefault)
		this->isDefault = "true";
	else this->isDefault = "false";
}

//----------SET FUNCTIONS----------
string Icon::getTitle() {
	return this->title;
}
string Icon::getImage() {
	return this->image;
}
string Icon::getObject() {
	return this->object;
}
string Icon::getDescription() {
	return this->description;
}
string Icon::getIsDefault() {
	return this->isDefault;
}