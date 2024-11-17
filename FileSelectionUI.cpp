#include<iostream>
using namespace std;

#include "FileSelectionUI.h"
#define hoverColor Green
#include<SFML/Graphics.hpp>
using namespace sf;

Font Menu::getFont() {
	return this->font;
}

int Menu::getSelectedFile() {
	return this->selected;
}

Menu::Menu() {
	selected = -1;
}

Menu::Menu(string files[10], string heading, Font& f, float width, float height) {
	this->font = f;
	setMenuItems(this->heading, this->font, Color::Blue, heading, 100, (width / 2), 5);
	this->heading.setPosition((width / 2) - (this->heading.getLocalBounds().width) / 2, 5);
	for (int i = 0; i < 10; i++) {
		if (i < 5)
			setMenuItems(filename[i], this->font, Color::White, files[i], 40, (width / 2) - 400, 300 + (i * 100));
		else
			setMenuItems(filename[i], this->font, Color::White, files[i], 40, (width / 2) + 400, 300 + ((i - 5) * 100));
	}
	selected = 0;
	this->filename[selected].setFillColor(Color::hoverColor);
}

void Menu::setMenuItems(Text& menu, Font& font, Color color, string text, unsigned int size, float x, float y) {
	menu.setFont(font);
	menu.setFillColor(color);
	menu.setString(text);
	menu.setCharacterSize(size);
	x = x - (menu.getGlobalBounds().width) / 2;
	menu.setPosition(x, y);
}

void Menu::MoveUp() {
	if (this->selected - 1 >= -1) {
		filename[this->selected].setFillColor(Color::White);
		this->selected--;
		if (this->selected == -1) {
			this->selected = 10 - 1;
		}
		this->filename[this->selected].setFillColor(Color::hoverColor);
	}
}

void Menu::MoveDown() {
	if (selected + 1 <= 10) {
		filename[selected].setFillColor(Color::White);
		this->selected++;
		if (selected == 10) {
			selected = 0;
		}
		this->filename[selected].setFillColor(Color::hoverColor);
	}
}

void Menu::MoveRight() {
	if (selected + 5 < 10) {
		filename[selected].setFillColor(Color::White);
		this->selected += 5;
		this->filename[selected].setFillColor(Color::hoverColor);
	}
	else {
		filename[selected].setFillColor(Color::White);
		this->selected -= 5;
		this->filename[selected].setFillColor(Color::hoverColor);
	}
}

void Menu::MoveLeft() {
	if (selected - 5 >= 0) {
		filename[selected].setFillColor(Color::White);
		this->selected -= 5;
		this->filename[selected].setFillColor(Color::hoverColor);
	}
	else {
		filename[selected].setFillColor(Color::White);
		this->selected += 5;
		this->filename[selected].setFillColor(Color::hoverColor);
	}
}

void Menu::showFileOptions(RenderWindow& menu) {

	menu.draw(this->heading);
	for (int i = 0; i < 10; i++) {
		menu.draw(this->filename[i]);
	}
}

void Menu::simulateSelection(RenderWindow& menu) {
	while (menu.isOpen())
	{
		Event event;
		while (menu.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				menu.close();
				return;
			}
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::Up) {
					this->MoveUp();
				}
				if (event.key.code == Keyboard::Down) {
					this->MoveDown();
				}
				if (event.key.code == Keyboard::Right) {
					this->MoveRight();
				}
				if (event.key.code == Keyboard::Left) {
					this->MoveLeft();
				}
				if (event.key.code == Keyboard::Return)
					return;
			}
		}

		menu.clear();
		this->showFileOptions(menu);
		menu.display();
	}
}