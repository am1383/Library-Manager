#include <iostream>
#include <fstream>
#include <unordered_map>

using namespace std;

class Book {
private:
    string bookName;
    string authorBook;
    int serialNumber;

public:
    string getBookName() const {
        return bookName;
    }

    string getAuthorBook() const {
        return authorBook;
    }

    int getSerialNumber() const {
        return serialNumber;
    }

    void setBookName(const string& bookNameR) {
        bookName = bookNameR;
    }

    void setAuthorBook(const string& authorBookR) {
        authorBook = authorBookR;
    }

    void setSerialNumber(const int& serialNumberR) {
        serialNumber = serialNumberR;
    }
};

void setMap(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, const string& bookRec, const int& serialNumber) {
    serialToString[serialNumber] = bookRec;
    stringToSerial[bookRec] = serialNumber;
}

string toLowerString(string& inputString) {
    for (int i = 0; i < inputString.size(); i++) {
        inputString[i] = tolower(inputString[i]);
    }
    return inputString;
}

void saveBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, const Book& book) {
    ofstream outPutFile(book.getBookName() + " Book.txt");
    if (outPutFile.is_open()) {
        outPutFile << book.getBookName() << '\n';
        outPutFile << book.getAuthorBook() << '\n';
        outPutFile << book.getSerialNumber() << '\n';

        setMap(stringToSerial, serialToString, book.getBookName(), book.getSerialNumber());

        outPutFile.close();

        cout << "Book Added To Library Successfully!" << '\n';
    } else {
        cout << "Unable To Open File, Please Contact Developers!" << '\n';
    }
}

void searchByID(unordered_map<int, string>& serialToString) {
    int ID;
    cout << "Please Enter ID: "; cin >> ID; cout << '\n';
    if (serialToString.find(ID) != serialToString.end()) {
        cout << "Book Found Successfully!" << '\n';
        cout << "Book Name: " << serialToString[ID] << '\n';
    } else {
        cout << "Invalid ID Number!" << '\n';
    }
}

void searchByName(unordered_map<string, int>& stringToSerial) {
    string inputSearchName;
    cout << "Please Enter Book Name: "; cin >> inputSearchName; cout << '\n';

    toLowerString(inputSearchName);

    if (stringToSerial.find(inputSearchName) != stringToSerial.end()) {
        cout << "Book Found Successfully!" << '\n';
        cout << "Book ID: " << stringToSerial[inputSearchName] << '\n';
    } else {
        cout << "Invalid Book Name!" << '\n';
    }
}

void searchSystem(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    int inputSearchID;

    cout << "Please Enter Search Choice: "; cin >> inputSearchID; cout << '\n';
    switch (inputSearchID) {
        case 1:
            searchByID(serialToString);
            break;
        case 2:
            searchByName(stringToSerial);
            break;
        default:
            cout << "Invalid Key, Please Try Again!" << '\n';
            break;
    }
}

void addBook(Book& book, unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    string inputString;
    int inputID;

    cout << "|---Add Book Page---|" << '\n' << '\n';
    cout << "Please Enter Book Name: "; cin >> inputString; book.setBookName(inputString);
    cout << "Please Enter Author Book Name: "; cin >> inputString; book.setAuthorBook(inputString);
    cout << "Please Enter Book Serial Number: "; cin >> inputID; book.setSerialNumber(inputID);

    saveBook(stringToSerial, serialToString, book);
}

void helpSystem() {
    cout << "|---Help Page---|" << '\n' << '\n';
    cout << "0 -> Help System "  << '\n';
    cout << "1 -> Adding Book "  << '\n';
    cout << "2 -> Reading Book " << '\n';
    cout << "3 -> Edit Book "    << '\n';
    cout << "4 -> Admin Panel"   << '\n';
}

int main() {
    unordered_map<string, int> stringToSerial;
    unordered_map<int, string> serialToString;

    Book book;
    int inputNumber;

    cout << "---------------------------------Book Management System---------------------------------" << '\n';

    do {
        cout << "> "; cin >> inputNumber; cout << '\n';
        switch (inputNumber) {
            case 0:
                helpSystem();
                break;
            case 1:
                addBook(book, stringToSerial, serialToString);
                break;
            case 2:
                searchSystem(stringToSerial, serialToString);
                break;
            case 3:
                //editBook();
                break;
            case 4:
                // adminPanel();
                break;
            default:
                //invalidSystem();
                break;
        }

    } while (inputNumber != 5);

    cout << "Thanks For Choosing Us!" << '\n';
    return 0;
}
