#include <iostream>
using namespace std;

void copyString(char* dest, const char* src, int maxSize) {
    int i = 0;
    while (src[i] != '\0' && i < maxSize - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

class Vehicle {
protected:
    int vehicleID;
    char manufacturer[50];
    char model[50];
    int year;
    static int totalVehicles;

public:
    Vehicle() {
        vehicleID = 0;
        manufacturer[0] = '\0';
        model[0] = '\0';
        year = 0;
        totalVehicles++;
    }

    Vehicle(int id, const char* mfr, const char* mdl, int yr) {
        vehicleID = id;
        copyString(manufacturer, mfr, 50);
        copyString(model, mdl, 50);
        year = yr;
        totalVehicles++;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }

    void setVehicleID(int id) { vehicleID = id; }
    void setManufacturer(const char* mfr) { copyString(manufacturer, mfr, 50); }
    void setModel(const char* mdl) { copyString(model, mdl, 50); }
    void setYear(int yr) { year = yr; }

    int getVehicleID() const { return vehicleID; }
    const char* getManufacturer() const { return manufacturer; }
    const char* getModel() const { return model; }
    int getYear() const { return year; }
    static int getTotalVehicles() { return totalVehicles; }

    virtual void input() {
        cout << "  Enter Vehicle ID   : ";
        cin >> vehicleID;
        cin.ignore(1000, '\n');

        cout << "  Enter Manufacturer : ";
        cin.getline(manufacturer, 50);

        cout << "  Enter Model        : ";
        cin.getline(model, 50);

        cout << "  Enter Year         : ";
        cin >> year;
        cin.ignore(1000, '\n');
    }

    virtual void display() const {
        cout << "  Vehicle ID   : " << vehicleID << endl;
        cout << "  Manufacturer : " << manufacturer << endl;
        cout << "  Model        : " << model << endl;
        cout << "  Year         : " << year << endl;
    }
};

int Vehicle::totalVehicles = 0;

class Car : public Vehicle {
protected:
    char fuelType[20];

public:
    Car() : Vehicle() {
        fuelType[0] = '\0';
    }

    Car(int id, const char* mfr, const char* mdl, int yr, const char* fuel)
        : Vehicle(id, mfr, mdl, yr) {
        copyString(fuelType, fuel, 20);
    }

    virtual ~Car() {}

    void setFuelType(const char* fuel) { copyString(fuelType, fuel, 20); }
    const char* getFuelType() const { return fuelType; }

    void input() {
        Vehicle::input();
        cout << "  Enter Fuel Type    : ";
        cin.getline(fuelType, 20);
    }

    void display() const {
        cout << "  [Type: Car]" << endl;
        Vehicle::display();
        cout << "  Fuel Type    : " << fuelType << endl;
    }
};

class ElectricCar : public Car {
protected:
    int batteryCapacity;

public:
    ElectricCar() : Car() {
        batteryCapacity = 0;
    }

    virtual ~ElectricCar() {}

    void setBatteryCapacity(int b) { batteryCapacity = b; }
    int getBatteryCapacity() const { return batteryCapacity; }

    void input() {
        Car::input();
        cout << "  Enter Battery Capacity (kWh) : ";
        cin >> batteryCapacity;
        cin.ignore(1000, '\n');
    }

    void display() const {
        cout << "  [Type: Electric Car]" << endl;
        Vehicle::display();
        cout << "  Fuel Type        : " << getFuelType() << endl;
        cout << "  Battery Capacity : " << batteryCapacity << " kWh" << endl;
    }
};

class Aircraft {
protected:
    int flightRange;

public:
    Aircraft() { flightRange = 0; }
    virtual ~Aircraft() {}

    void setFlightRange(int r) { flightRange = r; }
    int getFlightRange() const { return flightRange; }

    void inputAircraft() {
        cout << "  Enter Flight Range (km) : ";
        cin >> flightRange;
        cin.ignore(1000, '\n');
    }

    void displayAircraft() const {
        cout << "  Flight Range : " << flightRange << " km" << endl;
    }
};

class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar() : Car(), Aircraft() {}
    virtual ~FlyingCar() {}

    void input() {
        Car::input();
        inputAircraft();
    }

    void display() const {
        cout << "  [Type: Flying Car]" << endl;
        Vehicle::display();
        cout << "  Fuel Type    : " << getFuelType() << endl;
        displayAircraft();
    }
};

class SportsCar : public ElectricCar {
private:
    int topSpeed;

public:
    SportsCar() : ElectricCar() {
        topSpeed = 0;
    }

    virtual ~SportsCar() {}

    void setTopSpeed(int s) { topSpeed = s; }
    int getTopSpeed() const { return topSpeed; }

    void input() {
        ElectricCar::input();
        cout << "  Enter Top Speed (km/h) : ";
        cin >> topSpeed;
        cin.ignore(1000, '\n');
    }

    void display() const {
        cout << "  [Type: Sports Car]" << endl;
        Vehicle::display();
        cout << "  Fuel Type        : " << getFuelType() << endl;
        cout << "  Battery Capacity : " << getBatteryCapacity() << " kWh" << endl;
        cout << "  Top Speed        : " << topSpeed << " km/h" << endl;
    }
};

class Sedan : public Car {
public:
    Sedan() : Car() {}
    virtual ~Sedan() {}

    void input() { Car::input(); }

    void display() const {
        cout << "  [Type: Sedan]" << endl;
        Vehicle::display();
        cout << "  Fuel Type    : " << getFuelType() << endl;
    }
};

class SUV : public Car {
public:
    SUV() : Car() {}
    virtual ~SUV() {}

    void input() { Car::input(); }

    void display() const {
        cout << "  [Type: SUV]" << endl;
        Vehicle::display();
        cout << "  Fuel Type    : " << getFuelType() << endl;
    }
};

class VehicleRegistry {
private:
    Vehicle* vehicles[100];
    int total;

public:
    VehicleRegistry() { total = 0; }

    ~VehicleRegistry() {
        for (int i = 0; i < total; i++) {
            delete vehicles[i];
        }
    }

    void addVehicle() {
        cout << "\n  Select Vehicle Type:" << endl;
        cout << "  1. Car" << endl;
        cout << "  2. Electric Car" << endl;
        cout << "  3. Flying Car" << endl;
        cout << "  4. Sports Car" << endl;
        cout << "  5. Sedan" << endl;
        cout << "  6. SUV" << endl;
        cout << "  Enter type: ";

        int type;
        cin >> type;
        cin.ignore(1000, '\n');

        Vehicle* v = 0;
        if (type == 1) v = new Car();
        else if (type == 2) v = new ElectricCar();
        else if (type == 3) v = new FlyingCar();
        else if (type == 4) v = new SportsCar();
        else if (type == 5) v = new Sedan();
        else if (type == 6) v = new SUV();
        else {
            cout << "  Invalid type!" << endl;
            return;
        }

        cout << "\n  --- Enter Vehicle Details ---" << endl;
        v->input();
        vehicles[total++] = v;
        cout << "  Vehicle added successfully!" << endl;
    }

    void displayAll() const {
        if (total == 0) {
            cout << "  No vehicles found!" << endl;
            return;
        }
        cout << "\n  ====== All Vehicles ======" << endl;
        for (int i = 0; i < total; i++) {
            cout << "\n  --- Vehicle " << (i + 1) << " ---" << endl;
            vehicles[i]->display();
        }
        cout << "\n  Total Vehicles: " << Vehicle::getTotalVehicles() << endl;
    }

    void searchByID() const {
        int id;
        cout << "  Enter Vehicle ID to search: ";
        cin >> id;
        cin.ignore(1000, '\n');

        for (int i = 0; i < total; i++) {
            if (vehicles[i]->getVehicleID() == id) {
                cout << "\n  Vehicle Found!" << endl;
                vehicles[i]->display();
                return;
            }
        }
        cout << "  Vehicle with ID " << id << " not found!" << endl;
    }
};

int main() {
    VehicleRegistry registry;
    int choice;

    do {
        cout << "\n--- Vehicle Registry System Menu ---" << endl;
        cout << "1. Add a Vehicle" << endl;
        cout << "2. View All Vehicles" << endl;
        cout << "3. Search by ID" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        if (choice == 1) registry.addVehicle();
        else if (choice == 2) registry.displayAll();
        else if (choice == 3) registry.searchByID();
        else if (choice == 4) cout << "Exiting the system. Goodbye!" << endl;
        else cout << "Invalid choice! Try again." << endl;
    } while (choice != 4);

    return 0;
}
