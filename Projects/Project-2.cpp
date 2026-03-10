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

int compareString(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return (int)a[i] - (int)b[i];
        i++;
    }
    return (int)a[i] - (int)b[i];
}

class Train {
private:
    char trainName[50];
    char trainNumber[20];
    char startTime[20];
    char startPlace[50];
    char destination[50];
    static int trainCount;

public:
    Train() {
        trainName[0] = '\0';
        trainNumber[0] = '\0';
        startTime[0] = '\0';
        startPlace[0] = '\0';
        destination[0] = '\0';
        trainCount++;
    }

    Train(const char* name, const char* number, const char* time,
        const char* start, const char* dest) {
        setTrainName(name);
        setTrainNumber(number);
        setStartTime(time);
        setStartPlace(start);
        setDestination(dest);
        trainCount++;
    }

    ~Train() {}

    void setTrainName(const char* name) { copyString(trainName, name, 50); }
    void setTrainNumber(const char* number) { copyString(trainNumber, number, 20); }
    void setStartTime(const char* time) { copyString(startTime, time, 20); }
    void setStartPlace(const char* start) { copyString(startPlace, start, 50); }
    void setDestination(const char* dest) { copyString(destination, dest, 50); }

    const char* getTrainName() const { return trainName; }
    const char* getTrainNumber() const { return trainNumber; }
    const char* getStartTime() const { return startTime; }
    const char* getStartPlace() const { return startPlace; }
    const char* getDestination() const { return destination; }

    void inputTrainDetails() {
        cout << "Enter Train Name: ";
        cin.getline(trainName, 50);
        cout << "Enter Train Number: ";
        cin.getline(trainNumber, 20);
        cout << "Enter Start Time: ";
        cin.getline(startTime, 20);
        cout << "Enter Start Place: ";
        cin.getline(startPlace, 50);
        cout << "Enter Destination: ";
        cin.getline(destination, 50);
    }

    void displayTrainDetails() const {
        cout << "Train Name: " << trainName << endl;
        cout << "Train Number: " << trainNumber << endl;
        cout << "Start Time: " << startTime << endl;
        cout << "Start Place: " << startPlace << endl;
        cout << "Destination: " << destination << endl;
    }

    static int getTrainCount() { return trainCount; }
};

int Train::trainCount = 0;

class RailwaySystem {
private:
    Train trains[100];
    int count;

public:
    RailwaySystem() { count = 0; }

    void addTrain() {
        if (count >= 100) {
            cout << "Cannot add more trains." << endl;
            return;
        }
        trains[count].inputTrainDetails();
        count++;
    }

    void displayAllTrains() const {
        if (count == 0) {
            cout << "No train records found." << endl;
            return;
        }
        for (int i = 0; i < count; i++) {
            cout << "\n--- Train Record " << (i + 1) << " ---" << endl;
            trains[i].displayTrainDetails();
        }
    }

    void searchTrainByNumber() const {
        if (count == 0) {
            cout << "No train records to search." << endl;
            return;
        }
        char number[20];
        cout << "Enter Train Number to search: ";
        cin.getline(number, 20);

        for (int i = 0; i < count; i++) {
            if (compareString(trains[i].getTrainNumber(), number) == 0) {
                cout << "\nTrain Found:" << endl;
                trains[i].displayTrainDetails();
                return;
            }
        }
        cout << "Train not found." << endl;
    }
};

int main() {
    RailwaySystem system;
    int choice;

    do {
        cout << "\n--- Railway Reservation System Menu ---" << endl;
        cout << "1. Add New Train Record" << endl;
        cout << "2. Display All Train Records" << endl;
        cout << "3. Search Train by Number" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(1000, '\n');

        if (choice == 1) {
            system.addTrain();
        } else if (choice == 2) {
            system.displayAllTrains();
        } else if (choice == 3) {
            system.searchTrainByNumber();
        } else if (choice == 4) {
            cout << "Exiting the system. Goodbye..!" << endl;
        } else {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 4);

    return 0;
}
