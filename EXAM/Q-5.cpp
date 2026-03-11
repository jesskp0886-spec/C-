#include <iostream>
using namespace std;

class Animal {
public:
    virtual ~Animal() = default;
    virtual void sound() const = 0;
    virtual void move() const = 0;
};

class Dog : public Animal {
public:
    void sound() const override { cout << "Dog: Woof!\n"; }
    void move() const override { cout << "Dog: Runs.\n"; }
};

class Bird : public Animal {
public:
    void sound() const override { cout << "Bird: Chirp!\n"; }
    void move() const override { cout << "Bird: Fly.\n"; }
};

int main() {
    Animal* animals[2];
    animals[0] = new Dog();
    animals[1] = new Bird();

    for (int i = 0; i < 2; ++i) {
        animals[i]->sound();
        animals[i]->move();
    }

    for (int i = 0; i < 2; ++i) {
        delete animals[i];
    }

    return 0;
}
