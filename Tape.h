#include<SFML/Graphics.hpp>
#include<string>
using namespace std;
using namespace sf;

#ifndef TAPE_H
#define TAPE_H


class Tape {
public:
	RectangleShape container;
	Text value;
	Font font;
	Tape();
	void initializeTapeContainer(Vector2f, Vector2f);
	void initializeTapeValue(string);
	void setValuePosition();
	void setValueColor(Color);
};


#endif
