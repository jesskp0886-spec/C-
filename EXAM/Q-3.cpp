#include <iostream>
using namespace std;

class Shape {
private:
    char color[20];

public:
    virtual ~Shape() = default;

    void setColor(const char* c) {
        int i = 0;
        for (; c[i] != '\0' && i < 19; ++i) {
            color[i] = c[i];
        }
        color[i] = '\0';
    }
    const char* getColor() const { return color; }

    virtual double area() const = 0;
};

class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}
    double area() const override {
        const double pi = 3.14;
        return pi * radius * radius;
    }
};

class RectangleShape : public Shape {
private:
    double length;
    double width;

public:
    RectangleShape(double l, double w) : length(l), width(w) {}
    double area() const override { return length * width; }
};

int main() {
    Circle c(4);
    c.setColor("Red");

    RectangleShape r(6, 2);
    r.setColor("Blue");

    cout << "Circle color: " << c.getColor() << ", area: " << c.area() << "\n";
    cout << "Rectangle color: " << r.getColor() << ", area: " << r.area() << "\n";
    return 0;
}