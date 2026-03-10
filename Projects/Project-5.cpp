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

void readLine(const char* prompt, char* buf, int size) {
    cout << prompt;
    cin.getline(buf, size);
}

int readInt(const char* prompt, int minValue) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= minValue) {
            cin.ignore(1000, '\n');
            return value;
        }
        cout << "Invalid input. Try again.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

class LibraryItem {
protected:
    int itemID;
    char title[60];
    char author[50];
    bool checkedOut;

public:
    LibraryItem() {
        itemID = 0;
        title[0] = '\0';
        author[0] = '\0';
        checkedOut = false;
    }

    virtual ~LibraryItem() {}

    void setItemID(int id) { itemID = id; }
    int getItemID() const { return itemID; }

    void inputBase() {
        readLine("Enter Title  : ", title, 60);
        readLine("Enter Author : ", author, 50);
    }

    void displayBase() const {
        cout << "ID     : " << itemID << endl;
        cout << "Title  : " << title << endl;
        cout << "Author : " << author << endl;
        cout << "Status : " << (checkedOut ? "Checked Out" : "Available") << endl;
    }

    virtual void input() = 0;
    virtual void display() const = 0;
    virtual const char* getItemType() const = 0;

    virtual void checkOut() {
        if (checkedOut) cout << "Item already checked out.\n";
        else { checkedOut = true; cout << "Item checked out.\n"; }
    }

    virtual void returnItem() {
        if (!checkedOut) cout << "Item is already available.\n";
        else { checkedOut = false; cout << "Item returned.\n"; }
    }
};

class Book : public LibraryItem {
private:
    char isbn[20];

public:
    Book() { isbn[0] = '\0'; }
    ~Book() {}

    void input() {
        inputBase();
        readLine("Enter ISBN   : ", isbn, 20);
    }

    void display() const {
        cout << "[Book]\n";
        displayBase();
        cout << "ISBN   : " << isbn << endl;
    }

    const char* getItemType() const { return "Book"; }
};

class DVD : public LibraryItem {
private:
    int duration;

public:
    DVD() { duration = 0; }
    ~DVD() {}

    void input() {
        inputBase();
        duration = readInt("Enter Duration (minutes): ", 1);
    }

    void display() const {
        cout << "[DVD]\n";
        displayBase();
        cout << "Duration : " << duration << " minutes" << endl;
    }

    const char* getItemType() const { return "DVD"; }
};

class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine() { issueNumber = 0; }
    ~Magazine() {}

    void input() {
        inputBase();
        issueNumber = readInt("Enter Issue Number: ", 1);
    }

    void display() const {
        cout << "[Magazine]\n";
        displayBase();
        cout << "Issue Number : " << issueNumber << endl;
    }

    const char* getItemType() const { return "Magazine"; }
};

class Library {
private:
    LibraryItem* items[100];
    int count;
    int nextID;

public:
    Library() {
        count = 0;
        nextID = 1;
    }

    ~Library() {
        for (int i = 0; i < count; i++) delete items[i];
    }

    void addItem() {
        if (count >= 100) {
            cout << "Library is full.\n";
            return;
        }

        cout << "\nAdd Item Type:\n";
        cout << "1. Book\n";
        cout << "2. DVD\n";
        cout << "3. Magazine\n";
        int type = readInt("Enter choice: ", 1);

        LibraryItem* item = 0;
        if (type == 1) item = new Book();
        else if (type == 2) item = new DVD();
        else if (type == 3) item = new Magazine();
        else { cout << "Invalid type.\n"; return; }

        item->setItemID(nextID++);
        item->input();
        items[count++] = item;
        cout << "Item added successfully.\n";
    }

    void displayAll() const {
        if (count == 0) {
            cout << "No items in library.\n";
            return;
        }
        cout << "\n--- Library Items ---\n";
        for (int i = 0; i < count; i++) {
            cout << "\nItem " << (i + 1) << ":\n";
            items[i]->display();
        }
    }

    int findIndexByID(int id) const {
        for (int i = 0; i < count; i++) {
            if (items[i]->getItemID() == id) return i;
        }
        return -1;
    }

    void checkOutItem() {
        int id = readInt("Enter Item ID to check out: ", 1);
        int idx = findIndexByID(id);
        if (idx == -1) cout << "Item not found.\n";
        else items[idx]->checkOut();
    }

    void returnItem() {
        int id = readInt("Enter Item ID to return: ", 1);
        int idx = findIndexByID(id);
        if (idx == -1) cout << "Item not found.\n";
        else items[idx]->returnItem();
    }

    void removeItem() {
        int id = readInt("Enter Item ID to remove: ", 1);
        int idx = findIndexByID(id);
        if (idx == -1) {
            cout << "Item not found.\n";
            return;
        }
        delete items[idx];
        for (int i = idx; i < count - 1; i++) {
            items[i] = items[i + 1];
        }
        count--;
        cout << "Item removed.\n";
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n--- Library Management Menu ---\n";
        cout << "1. Add Item\n";
        cout << "2. Display All Items\n";
        cout << "3. Check Out Item\n";
        cout << "4. Return Item\n";
        cout << "5. Remove Item\n";
        cout << "6. Exit\n";
        choice = readInt("Enter choice: ", 1);

        if (choice == 1) lib.addItem();
        else if (choice == 2) lib.displayAll();
        else if (choice == 3) lib.checkOutItem();
        else if (choice == 4) lib.returnItem();
        else if (choice == 5) lib.removeItem();
        else if (choice == 6) cout << "Exiting...\n";
        else cout << "Invalid choice.\n";

    } while (choice != 6);

    return 0;
}
