#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, int> stringToSerial;
unordered_map<int, string> serialToString;

struct Book {

    string bookName, authorBook;
    int serialNumber;

};

    void setMap(const string& bookRec, const int& serialNumber) {


    serialToString [serialNumber] = bookRec;
    stringToSerial [bookRec] = serialNumber;
    }

void toLowerSting (string& inputString){

    for (int i=0; i<inputString.size(); i++){

        inputString[i] = tolower(inputString[i]);
    }
}

void saveBook (Book book) {

    ofstream outPutFile("Book.txt", ios::app);

    if (outPutFile.is_open()) {

        outPutFile << book.bookName << '\n';
        outPutFile << book.authorBook << '\n';
        outPutFile << book.serialNumber << '\n';

        setMap(book.bookName, book.serialNumber);

        outPutFile.close();

        cout << "Book Added To Libr8aray Sucessfuly !" << '\n';


    } else {

        cout << "Unable To Open File, Please Contact Developers !" << '\n';
    }

}

void searchByID () {
    int ID;
    cout << "Please Enter ID : "; cin >> ID; cout << '\n';
    if(serialToString[ID] != "") {

        cout << "Book Founded Sucessfuly !" << '\n';
        cout << "Book Name : " << serialToString[ID] << '\n';
    } else {

        cout << "Invalid ID Number !" << '\n';
    }

}

void searchByName () {

    string inputSearchName;
    cout << "Please Enter Book Name : "; cin >> inputSearchName; cout << '\n';

    toLowerSting(inputSearchName);

    if (stringToSerial[inputSearchName] != 0) {
        cout << "Book Founded Succesfuly !" << '\n' << '\n';
        cout << "Book ID : " << stringToSerial[inputSearchName] << '\n';
    } else {
        cout << "Invalid Book Name !" << '\n';
    }

}

void searchSystem (Book book) {

    string inputSearchString;
    int inputSearchID;

    cout << "Please Enter Search Choose : "; cin >> inputSearchID; cout << '\n';
    switch (inputSearchID) {
        case 1:
            searchByID();
            break;
        case 2:
            searchByName();
            break;
        default:
            cout << "Invalid Key, Please Try Again !" << '\n';
            break;
    }

}

void addBook (Book book) {

    cout << "Please Enter Book Name : "; cin >> book.bookName; cout << '\n';
    toLowerSting(book.bookName);
    cout << "Please Enter Author Book Name : "; cin >> book.authorBook; cout << '\n';
    cout << "Please Enter Book Serial Number : "; cin >> book.serialNumber; cout << '\n';

    saveBook(book);

}

void helpSystem () {

    cout << "0 -> Help System " << '\n';
    cout << "1 -> Adding Book " << '\n';
    cout << "2 -> Reading Book " << '\n';
    cout << "3 -> Edit Book " << '\n';
    cout << "4 -> Admin Panel" << '\n';
}

int main() {

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
                addBook(book);
                break;
            case 2:
                //readBook();
                searchSystem(book);
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

    }   while (inputNumber != 5); {

        cout << "Thanks For Choosing Us !" << '\n';
        exit(1);
    }
    return 0;
}
