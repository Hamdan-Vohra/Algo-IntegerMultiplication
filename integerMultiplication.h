#pragma once
//as we have defiend pragma so need to include headers
#include<SFML/Graphics.hpp>
#include<string>
#include<vector>
#include "Tape.h"

using namespace std;
using namespace sf;

//#define unsigned  long long

class intMultiplication {
    int num1, num2;
    vector<Tape> s1, s2;
    vector<Tape> c1, c2;
    vector<Tape> z;
    ConvexShape* arrow;
    Text stepText, X, Y, result;
    Font font;
public:
    intMultiplication();
    //Algorithms functions
    void Algorithm();
    int numDigits(int num);
    void setNumbers(int num1, int num2);
    long long  recursiveMultiply(int n1, int n2, RenderWindow& window);

    //visualization functions
    void visualizeStep(int n1, int n2, long long  result, RenderWindow& window, Color c);
    void draw(RenderWindow&);
    void display(RenderWindow&,int );

    //setter functions for GUI
    void setTape(Vector2u screenSize);
    void setStepText(RenderWindow&, int, int, int, Color c);
    void setXY(float);
    void setPartitionContainer(long long[2], long long[2], Vector2u);
    void setZ(long long[2], long long[2], long long[3], int, Vector2u);
    void setArrow(FloatRect, int);

    void resetArrowAndResult();
};


