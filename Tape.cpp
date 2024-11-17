#include "Tape.h"
#include<iostream>
using namespace std;

Tape::Tape() {
    if (!font.loadFromFile("Fonts/Roboto-Medium.ttf")) {
        cout << "No font is here" << endl;
        exit(0);
    }
}

void Tape::initializeTapeContainer(Vector2f size, Vector2f position) {
    container.setSize(size);
    container.setFillColor(Color::Transparent);
    container.setOutlineColor(Color::White);
    container.setOutlineThickness(2);
    container.setPosition(position);
}

void Tape::initializeTapeValue(string valueStr) {

    value.setFont(font);
    value.setString(valueStr);
    value.setCharacterSize(25);
    value.setFillColor(Color::Yellow);

    setValuePosition();
}
void Tape::setValueColor(Color c) {
    value.setFillColor(c);
}
void Tape::setValuePosition() {
    FloatRect containerBounds = container.getGlobalBounds();
    FloatRect textBounds = value.getLocalBounds();

    Vector2f position = Vector2f((containerBounds.left + containerBounds.width / 2) - (textBounds.width / 2), (containerBounds.top + containerBounds.height / 2) - (textBounds.height / 2));
    value.setPosition(position);
}
