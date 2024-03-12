#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Book {

    string bookName, authorBook;

    int serialNumber;

};

void    setMap(const string& bookRec, const int& serialNumber) {

    map<string, int> stringToSerial;
    map<int, string> serialToString;

    serialToString [serialNumber] = bookRec;
    stringToSerial [bookRec] = serialNumber;
}

void saveBook (Book book) {

    ofstream outPutFile("Book.txt", ios::app);

    if (outPutFile.is_open()) {

        outPutFile << book.bookName << endl;
        outPutFile << book.authorBook << endl;
        outPutFile << book.serialNumber << endl;

        setMap(book.bookName, book.serialNumber);

        outPutFile.close();

        cout << "Book Added To Libraray Sucessfuly !" << endl;


    } else {

        cout << "Unable To Open File, Please Contact Developers !" << endl;
    }

}


void addBook (Book book) {

    cout << "Please Enter Book Name : "; cin >> book.bookName; cout << endl;
    cout << "Please Enter Author Book Name : "; cin >> book.authorBook; cout << endl;
    cout << "Please Enter Book Serial Number : "; cin >> book.serialNumber; cout << endl;

    saveBook(book);

    return;

}

void helpSystem () {

    cout << "0 -> Help System " << endl;
    cout << "1 -> Adding Book " << endl;
    cout << "2 -> Reading Book " << endl;
    cout << "3 -> Edit Book " << endl;
    cout << "4 -> Admin Panel" << endl;
}

int main() {

    Book book;
    int inputNumber;

    cout << "---------------------------------Book Management System---------------------------------" << endl;
    //cout << " > "; cin >> inputNumber;

    do {
            cin >> inputNumber;
        switch (inputNumber) {

            case 0:
                helpSystem();
                break;
            case 1:
                addBook(book);
                break;
            case 2:
                //readBook();
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

        cout << "Thanks For Choosing Us !" << endl;
        exit(1);
    }
    return 0;
}
