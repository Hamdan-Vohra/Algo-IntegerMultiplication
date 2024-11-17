#pragma once
#include<SFML/Graphics.hpp>
#include<string>
using namespace std;
using namespace sf;

#ifndef FILESELECTION_H
#define FILESELECTION_H

class Menu {
	int selected;
	Text filename[10];
	Text heading;
	Font font;
public:
	Menu();
	Menu(string files[10], string, Font& f, float, float);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void simulateSelection(RenderWindow&);
	void showFileOptions(RenderWindow&);
	void setMenuItems(Text& menu, Font& font, Color color, string text, unsigned int size, float x, float y);
	Font getFont();
	int getSelectedFile();
};

//generic function for setting sfml elements properties
#endif 