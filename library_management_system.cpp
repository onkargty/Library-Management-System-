#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool issued;

    Book() : id(0), title(""), author(""), issued(false) {}

    void getBookDetails() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        issued = false;
    }

    void displayBook() const {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author;
        cout << ", Status: " << (issued ? "Issued" : "Available") << endl;
    }
};

vector<Book> books;

void saveBooksToFile() {
    ofstream file("books.dat", ios::binary | ios::out);
    for (const auto &book : books) {
        file.write((char*)&book, sizeof(Book));
    }
    file.close();
}

void loadBooksFromFile() {
    ifstream file("books.dat", ios::binary | ios::in);
    if (!file) return;
    books.clear();
    Book book;
    while (file.read((char*)&book, sizeof(Book))) {
        books.push_back(book);
    }
    file.close();
}

void addBook() {
    Book book;
    book.getBookDetails();
    books.push_back(book);
    saveBooksToFile();
    cout << "Book added successfully!" << endl;
}

void displayBooks() {
    if (books.empty()) {
        cout << "No books available.
";
        return;
    }
    for (const auto &book : books) {
        book.displayBook();
    }
}

void searchBook() {
    int id;
    cout << "Enter Book ID to search: ";
    cin >> id;
    for (const auto &book : books) {
        if (book.id == id) {
            book.displayBook();
            return;
        }
    }
    cout << "Book not found.
";
}

void issueBook() {
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;
    for (auto &book : books) {
        if (book.id == id && !book.issued) {
            book.issued = true;
            saveBooksToFile();
            cout << "Book issued successfully!
";
            return;
        }
    }
    cout << "Book not found or already issued.
";
}

void returnBook() {
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;
    for (auto &book : books) {
        if (book.id == id && book.issued) {
            book.issued = false;
            saveBooksToFile();
            cout << "Book returned successfully!
";
            return;
        }
    }
    cout << "Book not found or not issued.
";
}

int main() {
    loadBooksFromFile();
    int choice;
    do {
        cout << "
Library Management System
";
        cout << "1. Add Book
2. Display Books
3. Search Book
4. Issue Book
5. Return Book
6. Exit
";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: cout << "Exiting...
"; break;
            default: cout << "Invalid choice!
";
        }
    } while (choice != 6);
    return 0;
}
