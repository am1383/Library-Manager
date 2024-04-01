#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <unordered_map>

using namespace std;

class Book {

private:
    string bookName, bookDetails, authorBook;
    bool soldStatus;
    int serialNumber;

public:
    Book() : bookName(""), bookDetails(""), authorBook(""), soldStatus(false), serialNumber(0) {}

    string getBookName() const {return bookName;}
    string getAuthorBook() const {return authorBook;}
    string getBookDetails() const {return bookDetails;}
    bool getSoldStatus() const {return soldStatus;}
    int getSerialNumber() const {return serialNumber;}

    void setBookName(const string& bookNameR) {bookName = bookNameR;}
    void setAuthorBook(const string& authorBookR) {authorBook = authorBookR;}
    void setBookDetails(const string& bookDetailsR) {bookDetails = bookDetailsR;}
    void setSerialNumber(const int& serialNumberR) {serialNumber = serialNumberR;}
    void setSoldStatus(const bool& soldStatusR) {soldStatus = soldStatusR;}
};

//Function to check map changes
bool hasFileChanged(const unordered_map<string, int>& stringToSerial) {
    static size_t lastSize = sizeof(stringToSerial);

    size_t newSize = sizeof(stringToSerial);
    if (newSize != lastSize) {
        return true;
        lastSize = newSize;
    }
    return false;
}

void replaceLine(string& fileName, const int& lineNumber, string& newText) {
    ifstream inFile(fileName);

    vector<string> lines;
    string line;

    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    if (lineNumber == 1) {
        string newFileName = newText + " Book.txt";

        rename(fileName.c_str(), newFileName.c_str());
        fileName = newFileName;
    } else if (lineNumber == 2) {
        newText = "Author Name: " + newText;
    } else if (lineNumber == 3) {
        newText = "Book Details: " + newText;
    } else {
        cout << "Invalid Line Number, Please Try Again !" << '\n';
        return;
    }
    newText = "Book Name: " + newText;
    lines[lineNumber - 1] = newText;

    ofstream outFile(fileName);

    if (!outFile) {
        cout << "Unable To Open Book File, Please Contact Developers !" << '\n';
        return;
    }

    for (const string& l : lines) {
        outFile << l << '\n';
    }

    outFile.close();
    cout << "Book Details Updated Successfully !" << '\n';
}

// Function to load Map contents from a file
void loadMapFromFile(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
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

    bool flagFile = hasFileChanged(stringToSerial);
    if (!flagFile) {
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
        cout << "Unable To Open File To Load Map Data, Please Contact Developers !" << '\n';
        }
    }
}

//Function to save contents in Map file
void saveMapToFile(const unordered_map<string, int>& stringToSerial, const unordered_map<int, string>& serialToString) {
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
        cout << "Unable To Open File To Save Map Data, Please Contact Developers !" << '\n';
    }
}


void removeFromMapFile(const string& keyToRemove, unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    // Create a temporary Map to store contents of the file
    unordered_map<string, int> tempStringToSerial;
    unordered_map<int, string> tempSerialToString;

    // Read data from the file into the temporary Map
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
            cout << "Unable To Open File To Write Map data, Please Contact Developers !" << '\n';
        }
    } else {
        cout << "Unable To Open File To Read Map, Please Contact Developers !" << '\n';
        return;
    }
}

bool readBuyBook(const string& bookName) {
    ifstream fileCheck(bookName);
    if (fileCheck.is_open()) {
        fileCheck.close();
        return true;
    }
    return false;
}

void setMap(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, const string& bookName, const int& serialNumber) {
    serialToString[serialNumber] = bookName;
    stringToSerial[bookName] = serialNumber;
    saveMapToFile(stringToSerial, serialToString);
}

int getMapID(unordered_map<string, int>& stringToSerial, const string& inputString) {
    return stringToSerial[inputString];
}

string getMapString(unordered_map<int, string>& serialToSring, const int& inputID) {
    return serialToSring[inputID];
}

void saveBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, Book* book) {
    ofstream outPutFile(book->getBookName() + " Book.txt");
    if (outPutFile.is_open()) {
        outPutFile << "Book Name: " + book->getBookName() << '\n';
        outPutFile << "Book Author: " + book->getAuthorBook() << '\n';
        outPutFile << "Book Details: " + book->getBookDetails() << '\n';
        outPutFile << false << '\n';
        outPutFile << "Book ID: " << book->getSerialNumber() << '\n';
        outPutFile.close();

        setMap(stringToSerial, serialToString, book->getBookName(), book->getSerialNumber());

        cout << "Book Added To Library Successfully!" << '\n';
        } else {
            cout << "Unable To Add Book To Library, Please Contact Developers!" << '\n';
    }
}

void openBook(const string& inputBookName) {
    int lineNumber(0);
    ifstream inputFile(inputBookName);
    if (inputFile.is_open()) {
        string line;
        cout << '\n';
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string token;
            if (lineNumber < 3) {
                while (getline(iss, token, ',')) {
                    ++lineNumber;
                    cout << token << '\n';
                }
            }
        }
        inputFile.close();
        cout << '\n';
    } else {
        cout << "This Book Is Not Available, Please Try Another Book !" << '\n';
    }
}

bool checkValidationID(unordered_map<int, string>& serialToString, unordered_map<string, int>& stringToSerial, const int& numberRecieve) {
    loadMapFromFile(stringToSerial, serialToString);
    if (serialToString[numberRecieve] == "") {
        return 0;
    }
    return 1;
}

bool checkValidationString(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, const string& stringRecieve) {
    loadMapFromFile(stringToSerial, serialToString);
    if (stringToSerial[stringRecieve] == 0) {
        return 0;
    }
    return 1;
}

void addBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, Book* book) {
    string inputString;
    int inputID;

    cout << "> Add Book Page" << '\n' << '\n';
    cout << "Please Enter Book Name: "; cin >> inputString;

    while (checkValidationString(stringToSerial, serialToString, inputString)) {
        cout << "This Book Name Is Already Exist, Please Enter Another Book Name" << '\n';
        cout << "Please Enter Another Book Name: "; cin >> inputString; cout << '\n';
    }

    book->setBookName(inputString);

    cout << "Please Enter Author Book Name: "; cin >> inputString; book->setAuthorBook(inputString);
    cin.ignore();
    cout << "Please Enter Book Details: "; getline(cin, inputString); book->setBookDetails(inputString);
    cout << "Please Enter Book Serial Number: "; cin >> inputID;

    while (checkValidationID(serialToString, stringToSerial, inputID)) {
        cout << "This Book ID Is Already Exist, Please Enter Another ID" << '\n';
        cout << "Please Enter Another ID: "; cin >> inputID; cout << '\n';
    }

    book->setSoldStatus(false);
    book->setSerialNumber(inputID);
    saveBook(stringToSerial, serialToString, book);
}

void editBookInfo(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    string inputString, tempInputString, bookName;
    int inputNumber;
    cout << "> Edit Book Information" << '\n' << '\n';
    cout << "Please Enter Book Name: "; cin >> tempInputString;
    bookName = tempInputString;

    while(!checkValidationString(stringToSerial, serialToString, tempInputString)) {
        cout << "Invalid Book Name, Please Try Again !" << '\n';
        cout << "Please Enter New Book Name: "; cin >> tempInputString;
    }
    cout << "Please Enter Your Choose: "; cin >> inputNumber;

    switch (inputNumber) {
        case 1:
            cout << "Please Enter New Book Name: "; cin >> inputString;
            while(checkValidationString(stringToSerial, serialToString, inputString)) {
            cout << "This Book Name Is Already Exist, Please Enter New Name !" << '\n';
            cout << "Please Enter New Book Name: "; cin >> inputString;
            }
            tempInputString = tempInputString + " Book.txt";
            replaceLine(tempInputString, 1, inputString);
            break;

        case 2:
            cout << "Please Enter New Author Name: "; cin >> inputString;
            tempInputString = tempInputString + " Book.txt";
            replaceLine(tempInputString, 2, inputString);
            break;

        case 3:
            cin.ignore();
            cout << "Please Enter New Book Details: "; getline(cin, inputString);
            tempInputString = tempInputString + " Book.txt";
            replaceLine(tempInputString, 3, inputString);
            break;

        default:
            cout << "Invalid Key, Please Try Again !" << '\n';
            break;
    }
}

void readBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    int inputNumber;
    string inputString;

    cout << "> Read Book" << '\n' << '\n';
    cout << "Please Enter Book Name: "; cin >> inputString;
    inputString = inputString + " Archive.txt";
    if (readBuyBook(inputString)) {
        openBook(inputString);
    } else {
        cout << "This Book In Not In Your Archive, Please Try Again !" << '\n';
    }
}

void deleteBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    int inputNumber;
    string fileName, bookName;

    cout << "> Delete Book" << '\n' << '\n';
    cout << "Please Choose Your Selection: "; cin >> inputNumber;
    switch (inputNumber) {
        case 1:
            cout << "Please Enter Book ID: "; cin >> inputNumber;
            bookName = getMapString(serialToString, inputNumber);
            fileName = bookName + " Book.txt";
            break;
        case 2:
            cout << "Please Enter Book Name: "; cin >> bookName;
            fileName = bookName + " Book.txt";
            break;
        default:
            cout << "Invalid Key, Please Try Again !" << '\n';
            break;
        }

    if (remove(fileName.c_str())) {
            cout << "Book Name Is Not Exist, Please Try Again !" << '\n';
        } else {
            removeFromMapFile(bookName, stringToSerial, serialToString);
            cout << "Book " << bookName << " Successfully Deleted From Library !" << '\n';
    }
}

void updateFileSoldInfo(const string& bookName, const string& oldFileName, const string& newFileName) {
    ifstream readFile(newFileName);
    if (readFile.is_open()) {
        readFile.close();
        remove(oldFileName.c_str());
        cout << "Another Archive Of This File Is Already Exist !" << '\n';
        return;

    } else {
        if (rename(oldFileName.c_str(), newFileName.c_str()) != 0) {
            cout << "Unable To Rename File From " << oldFileName << " To " << newFileName << '\n';
            return;
        }
            ifstream inFile(newFileName);
            string line;
            string updatedContent;
            int lineNumber = 1;
            while (getline(inFile, line)) {

                if (lineNumber == 4) {
                    line = "1";
                }
                updatedContent += line + "\n";
                ++lineNumber;
            }
            inFile.close();

            ofstream outFile(newFileName);
            outFile << updatedContent;
            outFile.close();
            cout << "Book Added To Your Archive Sucessfuly !" << '\n';
    }

}

void buyBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    string inputString, tempInputString, inputBookName;
    cout << "> Buy Book" << '\n' << '\n';
    cout << "Please Enter Book Name: "; cin >> inputBookName;
    while(!checkValidationString(stringToSerial, serialToString, inputBookName)) {
        cout << "Book Name Is Invalid, Please Try Another Book Name" << '\n';
        cout << "Please Enter Book Name: "; cin >> inputBookName;
    }
    inputString = inputBookName + " Book.txt";
    tempInputString = inputBookName + " Archive.txt";

    if (getMapID(stringToSerial, inputString)) {
        cout << "This Book Is Already Sold, Please Try Again !" << '\n';
        return;
    }
    updateFileSoldInfo(inputBookName, inputString, tempInputString);
    removeFromMapFile(inputBookName, stringToSerial, serialToString);
}

//Function for print all bookName stored in files
void printAllBooks(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {

    cout << "> List Of All Books In The Library" << '\n';

    for (const auto& pair : serialToString) {
        cout << "Book Name: " << pair.second << " Book ID: " << pair.first << '\n';
    }
}

void helpMenu() {

    cout << "> Help Page\n\n"
         << "0 -> Help System\n"
         << "1 -> Add Book\n"
         << "2 -> Edit Book\n"
         << "3 -> Read Book\n"
         << "4 -> Delete Book\n"
         << "5 -> Print All Book\n"
         << "6 -> Exit\n";
}


int main() {
    unordered_map<string, int> stringToSerial;
    unordered_map<int, string> serialToString;

    loadMapFromFile(stringToSerial, serialToString);

    Book *book = new Book();
    int inputNumber;

    cout << "---------------------------------Book Management System---------------------------------" << '\n';

    do {
        cout << "> "; cin >> inputNumber;
            switch (inputNumber) {
                case 0:
                    helpMenu();
                    break;
                case 1:
                    addBook(stringToSerial, serialToString, book);
                    break;
                case 2:
                    editBookInfo(stringToSerial, serialToString);
                    break;
                case 3:
                    readBook(stringToSerial, serialToString);
                    break;
                case 4:
                    deleteBook(stringToSerial, serialToString);
                    break;
                case 5:
                    printAllBooks(stringToSerial, serialToString);
                    break;
                case 6:
                    buyBook(stringToSerial, serialToString);
                    break;
                case 7:
                    //Exit Case
                    break;
                default:
                    cout << "Invalid Command, Please Try Again!" << '\n';
                    break;
            }

        } while (inputNumber != 7); {
            cout << "C++ Beginning Project Created By Amir Mohammad Mousavi - 1401 Bu-Ali University" << '\n';
    }
        delete book;
        return 0;
}
