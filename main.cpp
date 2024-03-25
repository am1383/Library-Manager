#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <unordered_map>

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

//Function to check files changes
bool hasFileChanged() {
  static unordered_map<string, long> fileSizes; // Cache file sizes

  // Check if file exists in cache
  if (fileSizes.count("map.txt") > 0) {
    // Get file size
    ifstream file("map.txt");
    if (file.good()) {
      file.seekg(0, ios::end);
      long currentSize = file.tellg();

      // Compare sizes and update cache if changed
      if (currentSize != fileSizes["map.txt"]) {
        fileSizes["map.txt"] = currentSize;
        return true;
      }
      return false;
    } else {
      // Handle error opening file
      return false; // Consider throwing an exception for better error handling
    }
  } else {
    // Get file size for the first time
    ifstream file("map.txt");
    if (file.good()) {
      file.seekg(0, ios::end);
      long currentSize = file.tellg();
      fileSizes["map.txt"] = currentSize;
      return false;
    } else {
      // Handle error opening file
      return false; // Consider throwing an exception for better error handling
    }
  }
}

void replaceLine(const string& filename, const int& lineNumber, const string& newText) {
    ifstream inFile(filename);

    if (!inFile) {
        cout << "Unable To Open Book File, Please Contact Developers !" << '\n';
        return;
    }

    vector<string> lines;
    string line;

    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    if (lineNumber < 1 || lineNumber > lines.size()) {
        cout << "Invalid Line Number, Please Try Again !" << '\n';
        return;
    }

    lines[lineNumber - 1] = newText;

    ofstream outFile(filename);

    if (!outFile) {
        cout << "Unable To Open Book File, Please Contact Developers !" << '\n';
        return;
    }

    for (const string& l : lines) {
        outFile << l << endl;
    }

    outFile.close();

    cout << "Book Details Updated Successfully !" << '\n';
}

// Function to load Map contents from a file
void loadunordered_mapFromFile(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
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

    bool flagFile = hasFileChanged();
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
void saveunordered_mapToFile(const unordered_map<string, int>& stringToSerial, const unordered_map<int, string>& serialToString) {
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


void removeFromunordered_mapFile(const string& keyToRemove, unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
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

void setunordered_map(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, const string& bookRec, const int& serialNumber) {
    serialToString[serialNumber] = bookRec;
    stringToSerial[bookRec] = serialNumber;
    saveunordered_mapToFile(stringToSerial, serialToString);
}

int getunordered_mapID (unordered_map<string, int>& stringToSerial, const string& inputString) {
    return stringToSerial[inputString];
}

string getunordered_mapString (unordered_map<int, string>& serialToSring, const int& inputID) {
    return serialToSring[inputID];
}

void saveBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, Book& book) {
    ofstream outPutFile(book.getBookName() + " Book.txt");
    if (outPutFile.is_open()) {
        outPutFile << "Book Name: " + book.getBookName() << '\n';
        outPutFile << "Book Author: " + book.getAuthorBook() << '\n';
        outPutFile << "Book Details: " + book.getBookDetails() << '\n';
        outPutFile << "Book ID: " << book.getSerialNumber() << '\n';
        outPutFile.close();

        setunordered_map(stringToSerial, serialToString, book.getBookName(), book.getSerialNumber());

        cout << "Book Added To Library Successfully!" << '\n';
        } else {
            cout << "Unable To Add Book To Library, Please Contact Developers!" << '\n';
    }
}

void openBook(const string& inputBookName) {

    ifstream inputFile(inputBookName + " Book.txt");
    if (inputFile.is_open()) {
        string line;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string token;

    while (getline(iss, token, ',')) {
        cout << token << '\n';
            }
        }
        cout << '\n';
        inputFile.close();
    } else {
        cout << "This Book Is Not Available, Please Try Another Book !" << '\n';
    }
}

bool checkValidationID (unordered_map<int, string>& serialToString, unordered_map<string, int>& stringToSerial, const int& numberRecieve) {
    loadunordered_mapFromFile(stringToSerial, serialToString);
    if (serialToString[numberRecieve] == "") {
        return 0;
    }
    return 1;
}

bool checkValidationString (unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, const string& stringRecieve) {
    loadunordered_mapFromFile(stringToSerial, serialToString);
    if (stringToSerial[stringRecieve] == 0) {
        return 0;
    }
    return 1;
}

void addBook(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, Book& book) {
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
    cin.ignore();
    cout << "Please Enter Book Details: "; getline(cin, inputString); book.setBookDetails(inputString);
    cout << "Please Enter Book Serial Number: "; cin >> inputID;

    while (checkValidationID(serialToString, stringToSerial, inputID)) {
        cout << "This Book ID Is Already Exist, Please Enter Another ID" << '\n';
        cout << "Please Enter Another ID: "; cin >> inputID; cout << '\n';
    }

    book.setSerialNumber(inputID);
    saveBook(stringToSerial, serialToString, book);
}

void editBookInfo(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString, Book& book) {
    string inputString, tempInput;

    cout << "> Edit Book Information" << '\n' << '\n';
    cout << "Please Enter Book Name: "; cin >> tempInput;

    while(!checkValidationString(stringToSerial, serialToString, tempInput)) {
        cout << "Invalid Book Name, Please Try Again !" << '\n';
        cout << "Please Enter New Book Name: "; cin >> tempInput;
    }
        cout << "Please Enter New Book Details: "; cin >> inputString;
        book.setBookDetails(inputString);
        tempInput = tempInput + " Book.txt";
        replaceLine(tempInput, 3, inputString);

}

void readBook (unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    int inputNumber;
    string inputString;

    cout << "> Read Book" << '\n' << '\n';
    cout << "Please Enter Choose Search Selection: "; cin >> inputNumber;
    switch (inputNumber) {
        case 1:
            cout << "Please Enter Book ID: "; cin >> inputNumber; cout << '\n';
            if(checkValidationID(serialToString, stringToSerial, inputNumber)) {
                openBook(getunordered_mapString(serialToString, inputNumber));
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

void deleteBook (unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    int inputNumber;
    string fileName, bookName;

    cout << "> Delete Book" << '\n' << '\n';
    cout << "Please Choose Your Selection: "; cin >> inputNumber;
    switch (inputNumber) {
        case 1:
            cout << "Please Enter Book ID: "; cin >> inputNumber;
            bookName = getunordered_mapString(serialToString, inputNumber);
            fileName = bookName + " Book.txt";
            break;
        case 2:
            cout << "Please Enter Book Name: "; cin >> bookName;
            fileName = bookName + " Book.txt";
        default:
            cout << "Invalid Key, Please Try Again !" << '\n';
            break;
        }

    if (remove(fileName.c_str())) {
            cout << "Book Name Is Not Exist, Please Try Again !" << '\n';
        } else {
            removeFromunordered_mapFile(bookName, stringToSerial, serialToString);
            cout << "Book " << bookName << " Successfully Deleted Fromm Library !" << '\n';
    }
}

//Function for print all bookName stored in files
void printAllBooks(unordered_map<string, int>& stringToSerial, unordered_map<int, string>& serialToString) {
    bool flagFile = hasFileChanged();
    if (flagFile) {
        loadunordered_mapFromFile(stringToSerial, serialToString);
    }
    cout << "> List of all books in the library:" << '\n';

    for (const auto& pair : serialToString) {
        cout << "Book Name: " << pair.second << " Book ID: " << pair.first << '\n';
    }

}

void helpSystem() {

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

    loadunordered_mapFromFile(stringToSerial, serialToString);

    Book book;
    int inputNumber;

    cout << "---------------------------------Book Management System---------------------------------" << '\n';

    do {
        cout << "> "; cin >> inputNumber;
            switch (inputNumber) {
                case 0:
                    helpSystem();
                    break;
                case 1:
                    addBook(stringToSerial, serialToString, book);
                    break;
                case 2:
                    editBookInfo(stringToSerial, serialToString, book);
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
                    // Exit Case
                    break;
                default:
                    cout << "Invalid Command, Please Try Again!" << '\n';
                    break;
            }

        } while (inputNumber != 6); {
            cout << "C++ Beginning Project Created By Amir Mohammad Mousavi - 1401 Bu-Ali University";
    }
        return 0;
}
