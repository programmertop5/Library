#pragma once
#include <iostream>
#include <string>
#include "Book.h"
#include "Visitor.h"
using namespace std;

template<typename T>
class Library {
private:
    Book<T>* books;
    Visitor<T>* visitors;

    int currentBooks;
    int maxBooks;
    int currentVisitors;
    int maxVisitors;

public:
    Library(int maxBooks, int maxVisitors);
    ~Library();

    void addBook(const string& title, const string& author, const string& genre);
    void addVisitor(const string& surname, T id);

    Book<T>* searchByTitle(const string& title);
    void searchByAuthor(const string& author);
    void searchByGenre(const string& genre);

    bool giveBook(const string& title, T visitorId);
    bool returnBook(const string& title, T visitorId);

    T mostFrequentVisitor();
    void printAllBooks();
};



template<typename T>
Library<T>::Library(int maxB, int maxV) {
    maxBooks = maxB;
    maxVisitors = maxV;
    currentBooks = 0;
    currentVisitors = 0;

    books = new Book<T>[maxBooks];
    visitors = new Visitor<T>[maxVisitors];
}

template<typename T>
Library<T>::~Library() {
    delete[] books;
    delete[] visitors;
}

template<typename T>
void Library<T>::addBook(const string& title, const string& author, const string& genre) {
    if (currentBooks < maxBooks) {
        books[currentBooks] = Book<T>(title, author, genre);
        currentBooks++;
    }
}

template<typename T>
void Library<T>::addVisitor(const string& surname, T id) {
    if (currentVisitors < maxVisitors) {
        visitors[currentVisitors] = Visitor<T>(surname, id);
        currentVisitors++;
    }
}

template<typename T>
Book<T>* Library<T>::searchByTitle(const string& title) {
    for (int i = 0; i < currentBooks; i++) {
        if (books[i].title == title) {
            return &books[i];
        }
    }
    return nullptr;
}

template<typename T>
void Library<T>::searchByAuthor(const string& author) {
    for (int i = 0; i < currentBooks; i++) {
        if (books[i].author == author) {
            cout << books[i].title << " | " << books[i].genre;
            if (books[i].isTaken)
                cout << " | Taken by ID: " << books[i].takenById;
            cout << endl;
        }
    }
}

template<typename T>
void Library<T>::searchByGenre(const string& genre) {
    for (int i = 0; i < currentBooks; i++) {
        if (books[i].genre == genre) {
            cout << books[i].title << " | " << books[i].author;
            if (books[i].isTaken)
                cout << " | Taken by ID: " << books[i].takenById;
            cout << endl;
        }
    }
}

template<typename T>
bool Library<T>::giveBook(const string& title, T visitorId) {
    Visitor<T>* visitor = nullptr;

    for (int i = 0; i < currentVisitors; i++) {
        if (visitors[i].id == visitorId) {
            visitor = &visitors[i];
            break;
        }
    }

    if (!visitor || visitor->booksOnHand >= 3) return false;

    for (int i = 0; i < currentBooks; i++) {
        Book<T>& book = books[i];
        if (book.title == title && !book.isTaken) {
            book.isTaken = true;
            book.takenById = visitorId;
            visitor->booksOnHand++;
            visitor->visitCount++;
            return true;
        }
    }
    return false;
}

template<typename T>
bool Library<T>::returnBook(const string& title, T visitorId) {
    Visitor<T>* visitor = nullptr;

    for (int i = 0; i < currentVisitors; i++) {
        if (visitors[i].id == visitorId) {
            visitor = &visitors[i];
            break;
        }
    }
    if (!visitor) return false;

    for (int i = 0; i < currentBooks; i++) {
        Book<T>& book = books[i];
        if (book.title == title && book.isTaken && book.takenById == visitorId) {
            book.isTaken = false;
            book.takenById = T();
            visitor->booksOnHand--;
            return true;
        }
    }
    return false;
}

template<typename T>
T Library<T>::mostFrequentVisitor() {
    if (currentVisitors == 0) return T();
    int maxVisits = visitors[0].visitCount;
    int index = 0;
    for (int i = 1; i < currentVisitors; i++) {
        if (visitors[i].visitCount > maxVisits) {
            maxVisits = visitors[i].visitCount;
            index = i;
        }
    }
    return visitors[index].id;
}

template<typename T>
void Library<T>::printAllBooks() {
    for (int i = 0; i < currentBooks; i++) {
        cout << books[i].title << " | " << books[i].author << " | " << books[i].genre;
        if (books[i].isTaken) cout << " | Taken by ID: " << books[i].takenById;
        cout << endl;
    }
}
