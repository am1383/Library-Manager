#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

class Book {

    private:
        string bookName, bookDetails, authorBook;
        int serialNumber;

    public:
        Book() : bookName(""), bookDetails(""), authorBook(""), serialNumber(0) {}

        string getBookName() const {return bookName;}

        string getAuthorBook() const {return authorBook;}

        string getBookDetails () const {return bookDetails;}

        int getSerialNumber() const {return serialNumber;}

        void setBookName(const string& bookNameR) {bookName = bookNameR;}

        void setAuthorBook(const string& authorBookR) {authorBook = authorBookR;}

        void setSerialNumber(const int& serialNumberR) {serialNumber = serialNumberR;}

        void setBookDetails (const string& bookDetailsR) {bookDetails = bookDetailsR;}
};

void checkMapFromFile (map<string, int>& stringToSerial, map<int, string>& serialToString) {
    ifstream file("map.txt");

    if (file.good()) {

    } else {
        ofstream createFile("map.txt");
        if (createFile.is_open()) {
                createFile.close();

        } else {
            cout << "Unable To Open File, Please Contact Developers !" << '\n';
        }
    }
}
//Function to save contents in map file
void saveMapToFile(const map<string, int>& stringToSerial, const map<int, string>& serialToString) {
    ofstream outPutFile("map.txt");
    if (outPutFile.is_open()) {
        for (const auto& pair : stringToSerial) {
            outPutFile << pair.first << " " << pair.second << '\n';
        }
        for (const auto& pair : serialToString) {
            outPutFile << pair.first << " " << pair.second << '\n';
        }
        outPutFile.close();
    } else {
        cout << "Unable to open file to save map data, Please Contact Developers !" << '\n';
    }
}

// Function to load map contents from a file
void loadMapFromFile(map<string, int>& stringToSerial, map<int, string>& serialToString) {
    ifstream inputFile("map.txt");
    if (inputFile.is_open()) {
        string key;
        int value;
        while (inputFile >> key >> value) {
            stringToSerial[key] = value;
            serialToString[value] = key;
        }
        while (inputFile >> value >> key) {
            serialToString[value] = key;
            stringToSerial[key] = value;
        }
        inputFile.close();
    } else {
        cout << "Unable to open file to load map data." << '\n';
    }
}

void setMap(map<string, int>& stringToSerial, map<int, string>& serialToString, const string& bookRec, const int& serialNumber) {
    serialToString[serialNumber] = bookRec;
    stringToSerial[bookRec] = serialNumber;
    saveMapToFile(stringToSerial, serialToString);
    }

void saveBook(map<string, int>& stringToSerial, map<int, string>& serialToString, Book& book) {
    ofstream outPutFile(book.getBookName() + " Book.txt");
    if (outPutFile.is_open()) {
        outPutFile << book.getBookName() << '\n';
        outPutFile << book.getBookDetails() << '\n';
        outPutFile << book.getAuthorBook() << '\n';
        outPutFile << book.getSerialNumber() << '\n';
        outPutFile.close();

        setMap(stringToSerial, serialToString, book.getBookName(), book.getSerialNumber());

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

bool checkValidationID (map<int, string>& serialToString, map<string, int>& stringToSerial, const int& numberRecieve) {
    loadMapFromFile(stringToSerial, serialToString);
    if (serialToString[numberRecieve] == "") {
        return 0;
    }
    return 1;
}

bool checkValidationString (map<string, int>& stringToSerial, map<int, string>& serialToString, const string& stringRecieve) {
    loadMapFromFile(stringToSerial, serialToString);
    if (stringToSerial[stringRecieve] == 0) {
        return 0;
    }
    return 1;
}

void addBook(Book& book, map<string, int>& stringToSerial, map<int, string>& serialToString) {
    string inputString;
    int inputID;

    cout << "> Add Book Page" << '\n' << '\n';
    cout << "Please Enter Book Name: "; cin >> inputString;

    while (checkValidationString(stringToSerial, serialToString, inputString)) {
        cout << "This Book Name Is Already Exist, Please Enter Another Book Name" << '\n';
        cout << "Please Enter Another Book Name: "; cin >> inputString; cout << '\n';
    }

    book.setBookName(inputString);

    cout << "Please Enter Author Book Name: "; cin >> inputString; book.setAuthorBook(inputString);
    cout << "Please Enter Book Details: "; cin >> inputString; book.setBookDetails(inputString);
    cout << "Please Enter Book Serial Number: "; cin >> inputID;

    while (checkValidationID(serialToString, stringToSerial, inputID)) {
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
    // New change in book details will change to lower case
    for (int i = 0; i < inputString.length(); i++) {
        if (tempInput[i] != inputString[i]) {
            inputString[i] = tolower(inputString[i]);
        }
    }

    cout << "New Details Book :" << inputString << '\n';
    book.setBookDetails(inputString);
}

void readBook (Book& book, string& inputString, int& inputNumber, map<string, int>& stringToSerial, map<int, string>& serialToString) {
        cout << "Please Enter Choose Search Selection : "; cin >> inputNumber;

        switch (inputNumber) {
        case 1:
            cout << "Please Enter Book ID : "; cin >> inputNumber; cout << '\n';
            if(checkValidationID(serialToString, stringToSerial, inputNumber)) {
                openBook(book);
            } else {
                cout << "This Book Is Not Available, Please Try Again" << '\n';
            }
            break;

        case 2:
            cout << "Please Enter Book Name : "; cin >> inputString;
            if(checkValidationString(stringToSerial, serialToString, inputString)) {
                openBook(book);
            }

        default:
            cout << "Invalid Command, Please Try Again !" << '\n';
            break;
        }
    }

inline void helpSystem() {
    cout << "> Help Page" << '\n' << '\n';
    cout << "  0 -> Help System" << '\n';
    cout << "  1 -> Add Book" << '\n';
    cout << "  2 -> Search Book" << '\n';
    cout << "  3 -> Edit Book" << '\n';
    cout << "  4 -> Read Book" << '\n';
    cout << "  5 -> Exit" << '\n';
}


int main() {
    map<string, int> stringToSerial;
    map<int, string> serialToString;

    checkMapFromFile(stringToSerial, serialToString);
    loadMapFromFile(stringToSerial, serialToString);

    Book book;
    int inputNumber;
    string inputString;

    cout << "---------------------------------Book Management System---------------------------------" << '\n';

    do {
        cout << "> "; cin >> inputNumber;
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
                case 5:
                    exit(1);
                    break;
                default:
                    cout << "Invalid Command, Please Try Again!" << '\n';
                    break;
            }

        } while (inputNumber != 5);
            return 0;
}
