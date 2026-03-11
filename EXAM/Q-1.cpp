// Q-1: Rectangle class with setters/getters and area calculation
#include <iostream>

using namespace std;

class Rectangle {
private:
    double length;
    double width;

public:
    void setLength(double l) { length = l; }
    void setWidth(double w) { width = w; }
    double getLength() const { return length; }
    double getWidth() const { return width; }
    double area() const { return length * width; }
};

int main() {
    Rectangle r;
    r.setLength(5);
    r.setWidth(3);

    cout << "Length: " << r.getLength() << "\n";
    cout << "Width: " << r.getWidth() << "\n";
    cout << "Area: " << r.area() << "\n";
    return 0;
}
