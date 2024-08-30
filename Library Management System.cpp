#include <iostream>
#include <string>
#include <stdexcept>
#include <limits> 

using namespace std;

const int MAX_ITEMS = 10;

class LibraryItem {
protected:
    string title;
    string author;
    string dueDate;

public:
    LibraryItem(string t, string a, string d) : title(t), author(a), dueDate(d) {}

    virtual void checkOut() = 0;
    virtual void returnItem() = 0;
    virtual void displayDetails() const = 0;

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getDueDate() const { return dueDate; }
    
    void setTitle(string newTitle) { title = newTitle; }
    void setAuthor(string newAuthor) { author = newAuthor; }
    void setDueDate(string newDueDate) { dueDate = newDueDate; }
    
    virtual ~LibraryItem() {}
};

class Book : public LibraryItem {
private:
    string isbn;

public:
    Book(string t, string a, string d, string i) : LibraryItem(t, a, d), isbn(i) {}

    void checkOut() override {
        cout << "Book checked out: " << title << endl;
    }

    void returnItem() override {
        cout << "Book returned: " << title << endl;
    }

    void displayDetails() const override {
        cout << "Book: " << title << ", Author: " << author << ", ISBN: " << isbn << ", Due Date: " << dueDate << endl;
    }
};


class DVD : public LibraryItem {
private:
    int duration;
public:
    DVD(string t, string a, string d, int dur) : LibraryItem(t, a, d), duration(dur) {}

    void checkOut() override {
        cout << "DVD checked out: " << title << endl;
    }

    void returnItem() override {
        cout << "DVD returned: " << title << endl;
    }

    void displayDetails() const override {
        cout << "DVD: " << title << ", Author: " << author << ", Duration: " << duration << " minutes, Due Date: " << dueDate << endl;
    }
};


class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    Magazine(string t, string a, string d, int issue) : LibraryItem(t, a, d), issueNumber(issue) {}

    void checkOut() override {
        cout << "Magazine checked out: " << title << endl;
    }

    void returnItem() override {
        cout << "Magazine returned: " << title << endl;
    }

    void displayDetails() const override {
        cout << "Magazine: " << title << ", Author: " << author << ", Issue Number: " << issueNumber << ", Due Date: " << dueDate << endl;
    }
};


int getIntInput(const string& prompt) {
    int input;
    cout << prompt;
    while (!(cin >> input) || input < 0) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a positive integer: ";
    }
    return input;
}

string getStringInput(const string& prompt) {
    string input;
    cout << prompt;
    cin.ignore();
    getline(cin, input);
    return input;
}

int main() {
    LibraryItem* libraryItems[MAX_ITEMS];
    int itemCount = 0;
    int choice;

    
    libraryItems[itemCount++] = new Book("The Great Gatsby", "F. Scott Fitzgerald", "2024-12-01", "9780743273565");
    libraryItems[itemCount++] = new DVD("Inception", "Christopher Nolan", "2024-11-01", 148);
    libraryItems[itemCount++] = new Magazine("National Geographic", "Various", "2024-10-01", 202);

    while (true) {
        cout << "\nLibrary Management System" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Add DVD" << endl;
        cout << "3. Add Magazine" << endl;
        cout << "4. Display All Items" << endl;
        cout << "5. Check Out Item" << endl;
        cout << "6. Return Item" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string title = getStringInput("Enter book title: ");
                string author = getStringInput("Enter author: ");
                string dueDate = getStringInput("Enter due date (YYYY-MM-DD): ");
                string isbn = getStringInput("Enter ISBN: ");
                libraryItems[itemCount++] = new Book(title, author, dueDate, isbn);
                break;
            }
            case 2: {
                string title = getStringInput("Enter DVD title: ");
                string author = getStringInput("Enter director: ");
                string dueDate = getStringInput("Enter due date (YYYY-MM-DD): ");
                int duration = getIntInput("Enter duration (minutes): ");
                libraryItems[itemCount++] = new DVD(title, author, dueDate, duration);
                break;
            }
            case 3: {
                
                string title = getStringInput("Enter magazine title: ");
                string author = getStringInput("Enter publisher: ");
                string dueDate = getStringInput("Enter due date (YYYY-MM-DD): ");
                int issueNumber = getIntInput("Enter issue number: ");
                libraryItems[itemCount++] = new Magazine(title, author, dueDate, issueNumber);
                break;
            }
            case 4:
  
                for (int i = 0; i < itemCount; ++i) {
                    libraryItems[i]->displayDetails();
                }
                break;
            case 5: {
                  int index = getIntInput("Enter item index to check out (0 to " + to_string(itemCount - 1) + "): ");
                if (index >= 0 && index < itemCount) {
                    libraryItems[index]->checkOut();
                } else {
                    cout << "Invalid index." << endl;
                }
                break;
            }
            case 6: {
                int index = getIntInput("Enter item index to return (0 to " + to_string(itemCount - 1) + "): ");
                if (index >= 0 && index < itemCount) {
                    libraryItems[index]->returnItem();
                } else {
                    cout << "Invalid index." << endl;
                }
                break;
            }
            case 7:
                
                for (int i = 0; i < itemCount; ++i) {
                    delete libraryItems[i];
                }
                return 0;
            default:
                cout << "Invalid choice, try again." << endl;
        }
    }
}