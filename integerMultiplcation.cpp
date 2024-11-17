#include "integerMultiplication.h"
#include "Tape.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace sf;

#define BOXHEIGHT 60
//#define int long long int


intMultiplication::intMultiplication() : num1(0), num2(0) {
    if (!font.loadFromFile("Fonts/HaloDek.ttf")) {
        cerr << "Error loading font!" << endl;
        return;
    }
    this->c1.resize(2);
    this->c2.resize(2);
    this->z.resize(3);
    this->arrow = new ConvexShape(7);
}

//All setters Functionalities
void intMultiplication::setStepText(RenderWindow& window, int n1, int n2, int result, Color c) {
    if (!font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
        cerr << "Error loading Roboto font!" << endl;
        return;
    }
    stepText.setFont(font);
    stepText.setCharacterSize(24);
    stepText.setFillColor(c);
    stepText.setString("Step: " + to_string(n1) + " * " + to_string(n2) + " = " + (result == -1 ? "?" : to_string(result)));
    stepText.setPosition(50, window.getSize().y / 2);
}

void intMultiplication::setArrow(FloatRect z, int product) {
    float x = float(z.left + (0.5 * z.width));
    float y = float(z.top + z.height + 20);

    arrow->setPoint(0, Vector2f(x, y));
    arrow->setPoint(1, Vector2f(x, y + 40));
    arrow->setPoint(2, Vector2f(x - 8, y + 40));
    arrow->setPoint(3, Vector2f(x + 10, y + 60));
    arrow->setPoint(4, Vector2f(x + 28, y + 40));
    arrow->setPoint(5, Vector2f(x + 20, y + 40));
    arrow->setPoint(6, Vector2f(x + 20, y));
    arrow->setFillColor(Color::Cyan);

    if (!font.loadFromFile("Fonts/Roboto-Regular.ttf")) {
        cerr << "Error loading Roboto font!" << endl;
        return;
    }

    result.setFont(font);
    result.setCharacterSize(50);
    result.setFillColor(Color::Green);
    result.setString(to_string(product));

    FloatRect bounds = arrow->getGlobalBounds();
    result.setPosition(x - (result.getGlobalBounds().width / 2), y + bounds.height + 20);

}

void intMultiplication::setXY(float posY) {
    if (!font.loadFromFile("Fonts/HaloDek.ttf")) {
        cerr << "Error loading font!" << endl;
        return;
    }

    X.setFont(font);
    X.setCharacterSize(40);
    X.setFillColor(Color::White);
    Y.setFont(font);
    Y.setCharacterSize(40);
    Y.setFillColor(Color::White);

    X.setString("X: ");
    Y.setString("Y: ");

    X.setPosition(Vector2f(5.0, posY));
    Y.setPosition(Vector2f(5.0, posY + X.getPosition().y));
}

void intMultiplication::setPartitionContainer(long long  X[2], long long  Y[2], Vector2u screenSize) {
    int digits = max(max(numDigits(X[0]), numDigits(X[1])), max(numDigits(Y[0]), numDigits(Y[1])));
    int boxSizeX = (screenSize.x / 4);
    Vector2f size = Vector2f(boxSizeX, BOXHEIGHT);

    float posY = (screenSize.y / 2) - BOXHEIGHT;
    for (int i = 0; i < 2; i++) {
        Vector2f position = Vector2f((screenSize.x / 2) - (1 - i) * boxSizeX, posY);
        c1[i].initializeTapeContainer(size, position);
        c1[i].initializeTapeValue(to_string(X[i]));
    }


    for (int i = 0; i < 2; i++) {
        Vector2f position = Vector2f((screenSize.x / 2) - (1 - i) * boxSizeX, posY + c1[i].container.getGlobalBounds().height);
        c2[i].initializeTapeContainer(size, position);
        c2[i].initializeTapeValue(to_string(Y[i]));
    }
}

void intMultiplication::setZ(long long  X[2], long long  Y[2], long long  Z[3], int step, Vector2u screenSize) {

    float boxSizeX = screenSize.x / 5;
    float gap = 100.0;

    FloatRect bounds = this->c2[0].container.getGlobalBounds();
    float posY = bounds.height + bounds.top + gap;
    Vector2f position = Vector2f(screenSize.x / 7, posY);

    for (int i = 0; i < 3;) {
        Vector2f size = Vector2f(boxSizeX, BOXHEIGHT);
        if (i == 1) {
            size = Vector2f(2 * (screenSize.x / 6), BOXHEIGHT);
        }
        this->z[i].initializeTapeContainer(size, position);
        this->z[i].initializeTapeValue("No Value");
        i++;
        bounds = this->z[i - 1].container.getGlobalBounds();
        position = Vector2f(bounds.left + bounds.width, posY);
    }

    switch (step) {
    case 0:
        this->z[0].value.setString(to_string(X[1]) + "*" + to_string(Y[1]));
        this->z[1].value.setString(to_string(X[0] + X[1]) + "*" + to_string(Y[0] + Y[1]));
        this->z[2].value.setString(to_string(X[0]) + "*" + to_string(Y[0]));
        for (int i = 0; i < 3; i++) {
            this->z[i].value.setFillColor(Color::Red);
            this->z[i].setValuePosition();
        }
        break;
    case 1:
        this->z[0].value.setString(to_string(Z[0]));
        this->z[1].value.setString(to_string(X[0] + X[1]) + "*" + to_string(Y[0] + Y[1]));
        this->z[2].value.setString(to_string(X[0]) + "*" + to_string(Y[0]));
        for (int i = 0; i < 3; i++) {
            if (i < step)
                this->z[i].value.setFillColor(Color::Green);
            else
                this->z[i].value.setFillColor(Color::Red);
            this->z[i].setValuePosition();
        }
        break;
    case 2:
        this->z[0].value.setString(to_string(Z[0]));
        this->z[1].value.setString(to_string(Z[1]));
        this->z[2].value.setString(to_string(X[0]) + "*" + to_string(Y[0]));
        for (int i = 0; i < 3; i++) {
            if (i < step)
                this->z[i].value.setFillColor(Color::Green);
            else
                this->z[i].value.setFillColor(Color::Red);
            this->z[i].setValuePosition();
        }
        break;
    case 3:
        for (int i = 0; i < 3; i++) {
            if (i < step)
                this->z[i].value.setFillColor(Color::Green);
            else
                this->z[i].value.setFillColor(Color::Red);
            this->z[i].setValuePosition();
            this->z[i].value.setString(to_string(Z[i]));
        }
        break;
    }
}

void intMultiplication::setTape(Vector2u screenSize) {
    float posY = 100;
    setXY(posY + 5);

    float boxSizeX = screenSize.x / (max(numDigits(num1), numDigits(num2)) + 1);
    Vector2f size(boxSizeX, 60);

    // Initialize s1
    int n = num1;
    int elements = numDigits(num1);
    s1.resize(elements);
    for (int i = elements - 1; i >= 0; i--) {
        Vector2f position((elements - 1 - i) * boxSizeX + X.getGlobalBounds().width + 20, posY);
        s1[i].initializeTapeContainer(size, position);
        s1[i].initializeTapeValue(to_string(n % 10));
        n /= 10;
    }

    // Initialize s2
    n = num2;
    elements = numDigits(num2);
    s2.resize(elements);
    for (int i = elements - 1; i >= 0; i--) {
        Vector2f position((elements - 1 - i) * boxSizeX + X.getGlobalBounds().width + 20, s1[0].container.getPosition().y + posY);
        s2[i].initializeTapeContainer(size, position);
        s2[i].initializeTapeValue(to_string(n % 10));
        n /= 10;
    }
}

//Draw and Display
void intMultiplication::draw(RenderWindow& window) {
    window.draw(stepText);
    window.draw(X);
    window.draw(Y);
    window.draw(*arrow);
    window.draw(result);

    for (const auto& tape : s1) {
        window.draw(tape.container);
        window.draw(tape.value);
    }
    for (const auto& tape : s2) {
        window.draw(tape.container);
        window.draw(tape.value);
    }
    for (const auto& tape : c1) {
        window.draw(tape.container);
        window.draw(tape.value);
    }
    for (const auto& tape : c2) {
        window.draw(tape.container);
        window.draw(tape.value);
    }
    for (const auto& tape : z) {
        window.draw(tape.container);
        window.draw(tape.value);
    }
}

void intMultiplication::display(RenderWindow& window) {
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return;
            }
            if (event.type == Event::KeyReleased && event.key.code == Keyboard::Right) {
                return;
            }
        }
        window.clear();
        draw(window);
        window.display();

        //simulation time
        sf::sleep(sf::seconds(1));
        return;
    }
}

//Resetting Functionalities
void intMultiplication::resetArrowAndResult() {
    delete this->arrow;
    this->arrow = new ConvexShape(7);
    result = Text();
}

//Algorithm related Functions
int intMultiplication::numDigits(int num) {

    int digits = 0;
    while (num) {
        digits++;
        num /= 10;
    }
    return digits;
}

void intMultiplication::setNumbers(int num1, int num2) {
    this->num1 = num1;
    this->num2 = num2;
}

void intMultiplication::Algorithm() {
    RenderWindow window(VideoMode::getDesktopMode(), "Integer Multiplication Visualization", Style::Default);

    // Visualize the input numbers
    setTape(window.getSize());

    // Start recursive multiplication
    long long  result = recursiveMultiply(num1, num2, window);

    // Final result visualization
    cout << "Product of " << num1 << " and " << num2 << " is " << result << endl;
    window.clear();

    //setting product results
    Text product;
    product.setFont(font);
    product.setCharacterSize(50);
    product.setFillColor(Color::Yellow);
    product.setString(to_string(num1) + " * " + to_string(num2) + " : " + to_string(result));
    FloatRect bounds = product.getGlobalBounds();
    Vector2u screenSize = window.getSize();
    product.setPosition(Vector2f((screenSize.x / 2) - (bounds.width / 2), (screenSize.y / 2) - 50));
    
    window.draw(product);
    window.display();
    sf::sleep(sf::seconds(5));
    window.close();
}

long long  intMultiplication::recursiveMultiply(int n1, int n2, RenderWindow& window) {
    // Base case
    if (n1 < 10 || n2 < 10) {
        int product = n1 * n2;

        // Visualize base case multiplication
        long long X[2] = { 0,n1 };
        long long Y[2] = { 0,n2 };
        Vector2u screenSize = window.getSize();
        setPartitionContainer(X, Y, screenSize);
        visualizeStep(n1, n2, product, window, Color::Green);


        return product;
    }


    int n1Digits = numDigits(n1);
    int n2Digits = numDigits(n2);
    int n = max(n1Digits, n2Digits);
    int half = n / 2;

    // Split both numbers into two parts : high and low
    long long  highX = n1 / pow(10, half);
    long long  lowX = n1 % static_cast<int>(pow(10, half));
    long long  highY = n2 / pow(10, half);
    long long  lowY = n2 % static_cast<int>(pow(10, half));

    long long  X[2] = { highX,lowX };
    long long  Y[2] = { highY,lowY };
    long long  Z[3] = { 0 };
    Vector2u screenSize = window.getSize();
    setPartitionContainer(X, Y, screenSize);
    setZ(X, Y, Z, 0, screenSize);
    visualizeStep(n1, n2, -1, window, Color::Red);

    // Recursive calls
    Z[0] = recursiveMultiply(lowX, lowY, window);
    setPartitionContainer(X, Y, screenSize);
    setZ(X, Y, Z, 1, screenSize);
    visualizeStep(lowX, lowY, Z[0], window, Color::Green);

    Z[1] = recursiveMultiply((lowX + highX), (lowY + highY), window);
    setPartitionContainer(X, Y, screenSize);
    setZ(X, Y, Z, 2, screenSize);
    visualizeStep((lowX + highX), (lowY + highY), Z[1], window, Color::Green);

    Z[2] = recursiveMultiply(highX, highY, window);
    setPartitionContainer(X, Y, screenSize);
    setZ(X, Y, Z, 3, screenSize);
    visualizeStep(highX, highY, Z[2], window, Color::Green);



    // Combine results
    long long  product = Z[2] * pow(10, 2 * half) + (Z[1] - Z[2] - Z[0]) * pow(10, half) + Z[0];

    // Visualize intermediate results
    FloatRect bounds = z[1].container.getGlobalBounds();
    setArrow(bounds, product);
    setPartitionContainer(X, Y, window.getSize());
    visualizeStep(n1, n2, product, window, Color::Green);

    resetArrowAndResult();
    return product;
}

//Visualization Function
void intMultiplication::visualizeStep(int n1, int n2, long long  result, RenderWindow& window, Color c) {

    if (result == -1)
        cout << "Multiplying " << n1 << " and " << n2 << " = " << "No result" << endl;
    else
        cout << "Multiplying " << n1 << " and " << n2 << " = " << result << endl;

    setStepText(window, n1, n2, result, c);

    draw(window);
    display(window);
    window.clear();
}