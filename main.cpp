#include <iostream>
#include <iomanip>
#include <fstream>
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
            cout << "Unable To Open Map File, Please Contact Developers !" << '\n';
        }
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
        cout << "Unable to open file to load map data, Please Contact Developers !" << '\n';
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

void removeFromMapFile(const string& keyToRemove, map<string, int>& stringToSerial, map<int, string>& serialToString) {
    // Create a temporary map to store contents of the file
    map<string, int> tempStringToSerial;
    map<int, string> tempSerialToString;

    // Read data from the file into the temporary map
    ifstream inFile("map.txt");
    if (inFile.is_open()) {
        string key;
        int value;
        while (inFile >> key >> value) {
            if (key != keyToRemove) { // Skip the key to remove
                tempStringToSerial[key] = value;
                tempSerialToString[value] = key;
            }
        }
        inFile.close();

        // Write data back to the file excluding the key to remove
        ofstream outFile("map.txt");
        if (outFile.is_open()) {
            for (const auto& pair : tempStringToSerial) {
                outFile << pair.first << " " << pair.second << '\n';
            }
            for (const auto& pair : tempSerialToString) {
                outFile << pair.first << " " << pair.second << '\n';
            }
            outFile.close();
            stringToSerial = tempStringToSerial;
            serialToString = tempSerialToString;
        } else {
            cout << "Unable to open file to write map data, Please Contact Developers !" << '\n';
        }
    } else {
        cout << "Unable to open file to read map data, Please Contact Developers !" << '\n';
        return;
    }
}

void setMap(map<string, int>& stringToSerial, map<int, string>& serialToString, const string& bookRec, const int& serialNumber) {
    serialToString[serialNumber] = bookRec;
    stringToSerial[bookRec] = serialNumber;
    saveMapToFile(stringToSerial, serialToString);
}

int getMapID (map<string, int>& stringToSerial, const string& inputString) {
    return stringToSerial[inputString];
}

string getMapString (map<int, string>& serialToSring, const int& inputID) {
    return serialToSring[inputID];
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

void openBook(const string& inputBookName) {

    ifstream inputFile(inputBookName + " Book.txt");
    if (inputFile.is_open()) {
        string line;
        cout << inputBookName + " Book Details: " << '\n';

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string token;

    while (getline(iss, token, ',')) {
        cout << token << '\n';
            }
        }
        cout << '\n';
    } else {
        cout << "This Book Is Not Available, Please Try Another Book !" << '\n';
    }
}

bool checkValidationID (map<int, string>& serialToString, map<string, int>& stringToSerial, const int& numberRecieve) {
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
    for (int i=0; i < inputString.length(); i++) {
        if (tempInput[i] != inputString[i]) {
            inputString[i] = tolower(inputString[i]);
        }
    }

    cout << "New Details Book:" << inputString << '\n';
    book.setBookDetails(inputString);
}

void readBook (string& inputString, int& inputNumber, map<string, int>& stringToSerial, map<int, string>& serialToString) {
    cout << "Please Enter Choose Search Selection: "; cin >> inputNumber;

    switch (inputNumber) {
    case 1:
        cout << "Please Enter Book ID: "; cin >> inputNumber; cout << '\n';
        if(checkValidationID(serialToString, stringToSerial, inputNumber)) {
            openBook(getMapString(serialToString, inputNumber));
        } else {
            cout << "This Book Is Not Available, Please Try Again" << '\n';
        }
        break;

    case 2:
        cout << "Please Enter Book Name: "; cin >> inputString;
        if(checkValidationString(stringToSerial, serialToString, inputString)) {
            openBook(inputString);
        }
        break;
    default:
        cout << "Invalid Command, Please Try Again !" << '\n';
        break;
    }
}

void deleteBook (map<string, int>& stringToSerial, map<int, string>& serialToString, string& bookName) {

    cout << "Please Enter Book Name: "; cin >> bookName;
    string fileName = bookName + " Book.txt";

    if (remove(fileName.c_str())) {
            cout << "Error Deleting File, Please Contact Developers !" << '\n';
        } else {
            removeFromMapFile(bookName, stringToSerial, serialToString);
            cout << "Book Successfully Deleted Form Library" << '\n';
    }
}

void helpSystem() {
    cout << "> Help Page" << '\n' << '\n';
    cout << "0 -> Help System" << '\n';
    cout << "1 -> Add Book" << '\n';
    cout << "2 -> Search Book" << '\n';
    cout << "3 -> Edit Book" << '\n';
    cout << "4 -> Read Book" << '\n';
    cout << "5 -> Exit" << '\n';
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
                    readBook(inputString, inputNumber, stringToSerial, serialToString);
                    break;
                case 4:
                    deleteBook(stringToSerial, serialToString, inputString);
                    break;
                case 5:
                    exit(1);
                    break;
                default:
                    cout << "Invalid Command, Please Try Again!" << '\n';
                    break;
            }

        } while (true);

             return 0;
}
