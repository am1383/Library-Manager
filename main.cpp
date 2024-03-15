#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>

using namespace std;

class Book {

    private:
        string bookName, bookDetails, authorBook;
        int serialNumber;

    public:
        Book() : bookName(""), bookDetails(""), authorBook(""), serialNumber(0) {}

        string getBookName() const {
            return bookName;
        }

        string getAuthorBook() const {
            return authorBook;
        }

        string getBookDetails () const {
            return bookDetails;
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

        void setBookDetails (const string& bookDetailsR) {
            bookDetails = bookDetailsR;
        }
};

void setMap(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, const string& bookRec, const int& serialNumber, Book& book) {
    serialToString[serialNumber] = bookRec;
    stringToSerial[bookRec] = serialNumber;
    }

void saveBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, Book& book) {
    ofstream outPutFile(book.getBookName() + " Book.txt");
    if (outPutFile.is_open()) {
        outPutFile << book.getBookName() << '\n';
        outPutFile << book.getBookDetails() << '\n';
        outPutFile << book.getAuthorBook() << '\n';
        outPutFile << book.getSerialNumber() << '\n';

        setMap(stringToSerial, serialToString, book.getBookName(), book.getSerialNumber(), book);

        outPutFile.close();

        cout << "Book Added To Library Successfully!" << '\n';
        } else {
            cout << "Unable To Open File, Please Contact Developers!" << '\n';
        }
}

void openBook(Book& book) {
    ifstream inputFile(book.getBookName() + " Book.txt");

    if (inputFile.is_open()) {
        string line;
        cout << book.getBookName() + " Book Details :" << '\n';

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string token;

    while (getline(iss, token, ',')) {
        cout << token << '\n';
            }
        }
        cout << '\n';
    } else {
        cout << "Unable To Open File, Please Contact Developers!" << '\n';
    }
}

bool checkValidationID (unordered_map<int, string>& serialToString, const int& numberRecieve) {
    if (serialToString[numberRecieve] == "") {
        return 0;
    }
    return 1;
}

bool checkValidationString (unordered_map<string, int>& stringToSerial, const string& stringRecieve) {
    if (stringToSerial[stringRecieve] == 0) {
        return 0;
    }
    return 1;
}

void addBook(Book& book, unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    string inputString;
    int inputID;

    cout << "> Add Book Page" << '\n' << '\n';
    cout << "Please Enter Book Name: "; cin >> inputString;

    while (checkValidationString(stringToSerial, inputString)) {
        cout << "This Book Name Is Already Exist, Please Enter Another Book Name" << '\n';
        cout << "Please Enter Another Book Name: "; cin >> inputString; cout << '\n';
    }

    book.setBookName(inputString);

    cout << "Please Enter Author Book Name: "; cin >> inputString; book.setAuthorBook(inputString);
    cout << "Please Enter Book Details: "; cin >> inputString; book.setBookDetails(inputString);
    cout << "Please Enter Book Serial Number: "; cin >> inputID;

    while (checkValidationID(serialToString, inputID)) {
        cout << "This Book ID Is Already Exist, Please Enter Another ID" << '\n';
        cout << "Please Enter Another ID: "; cin >> inputID; cout << '\n';
    }

    book.setSerialNumber(inputID);

    saveBook(stringToSerial, serialToString, book);
}

void editBookInfo(Book& book) {
    string inputString;
    string tempInput = book.getBookDetails();

    cout << "Please Enter New Book Details: "; cin >> inputString;

    inputString.resize(inputString.length());

    for (int i = 0; i < inputString.length(); i++) {
        if (tempInput[i] != inputString[i]) {
            inputString[i] = tolower(inputString[i]);
        }
    }

    cout << "New Details Book :" << inputString << '\n';
    book.setBookDetails(inputString);
}

void readBook (Book& book, string& inputString, int& inputNumber, unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
        cout << "Please Enter Choose Search Selection : "; cin >> inputNumber;

        switch (inputNumber) {
        case 1:
            cout << "Please Enter Book ID : "; cin >> inputNumber; cout << '\n';
            if(checkValidationID(serialToString, inputNumber)) {
                openBook(book);
            } else {
                cout << "This Book Is Not Available, Please Try Again" << '\n';
            }
            break;

        case 2:
            cout << "Please Enter Book Name : "; cin >> inputString;
            if(checkValidationString(stringToSerial, inputString)) {
                openBook(book);
            }

        default:
            break;
        }
    }

void helpSystem() {
    cout << "> Help Page"       << '\n' << '\n';
    cout << "0 -> Help System"  << '\n';
    cout << "1 -> Adding Book"  << '\n';
    cout << "2 -> Search Book"  << '\n';
    cout << "3 -> Edit Book"    << '\n';
    cout << "4 -> Read Book"    << '\n';
}

int main() {
    unordered_map<string, int> stringToSerial;
    unordered_map<int, string> serialToString;

    Book book;
    int inputNumber(0);
    string inputString("");

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
                    editBookInfo(book);
                    break;
                case 3:
                    readBook(book, inputString, inputNumber, stringToSerial, serialToString);
                    break;
                default:
                    break;
            }

        } while (inputNumber != 5);
            return 0;
}
