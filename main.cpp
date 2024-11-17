#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;

#include "FileSelectionUI.h"
#include "integerMultiplication.h"


int main()
{
    Font font;
    string files[10];
    for (int i = 0; i < 10; i++) {
        string file = "IntegerMultiplication_";
        file += to_string(i + 1);
        file += ".txt";

        files[i] = file;
    }

    if (!font.loadFromFile("Fonts/HaloDek.ttf")) {
        cout << "No font is here" << endl;
        exit(0);
    }
    else {
        cout << "Font is Included" << endl;
    }

    RenderWindow window(VideoMode::getDesktopMode(), "File Selection", Style::Close);

    string heading = "Integer Multiplication";
    Menu *m = new Menu(files,heading,font,window.getSize().x, window.getSize().y);
    m->simulateSelection(window);

    int fileSelected = m->getSelectedFile();
    string filePath= "Files/";
    filePath += files[fileSelected];
    const char* selectedFile = filePath.data(); 

    FILE* file;
    int num1, num2;

    if (fopen_s(&file, selectedFile, "r") != 0) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    if (fscanf_s(file, "%d", &num1) != 1) {
        printf("Error: Could not read the first number.\n");
        fclose(file);
        return 1;
    }

    if (fscanf_s(file, "%d", &num2) != 1) {
        printf("Error: Could not read the second number.\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    printf("First number: %d\n", num1);
    printf("Second number: %d\n", num2);

    intMultiplication multiplier;
    multiplier.setNumbers(num1, num2);
    multiplier.Algorithm();
    return 0;

    return 0;
}