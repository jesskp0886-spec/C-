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
    virtual void display() const = 0;
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
    void display() const override {
        cout << "Circle | color=" << getColor()
            << " | radius=" << radius
            << " | area=" << area() << "\n";
    }
};

class RectangleShape : public Shape {
private:
    double length;
    double width;

public:
    RectangleShape(double l, double w) : length(l), width(w) {}
    double area() const override { return length * width; }
    void display() const override {
        cout << "Rectangle | color=" << getColor()
            << " | length=" << length
            << " | width=" << width
            << " | area=" << area() << "\n";
    }
};

int main() {
    Shape* shapes[2];

    Circle* c = new Circle(4);
    c->setColor("Red");
    shapes[0] = c;

    RectangleShape* r = new RectangleShape(6, 2);
    r->setColor("Blue");
    shapes[1] = r;

    for (int i = 0; i < 2; ++i) {
        shapes[i]->display();
    }

    for (int i = 0; i < 2; ++i) {
        delete shapes[i];
    }

    return 0;
}
