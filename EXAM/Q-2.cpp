#include <iostream>
#include <string>

using namespace std;

class Employee {
private:
    string name;
    double salary;
    string designation;

public:
    void setName(const string& n) { name = n; }
    void setSalary(double s) { salary = s; }
    void setDesignation(const string& d) { designation = d; }

    string getName() const { return name; }
    double getSalary() const { return salary; }
    string getDesignation() const { return designation; }
};

int main() {
    Employee e;
    e.setName("Jiya");
    e.setSalary(45000);
    e.setDesignation("Fullstack-Developer");

    cout << "Name: " << e.getName() << "\n";
    cout << "Salary: " << e.getSalary() << "\n";
    cout << "Designation: " << e.getDesignation() << "\n";
    return 0;
}
