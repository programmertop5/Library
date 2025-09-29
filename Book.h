#pragma once
#include <string>
using namespace std;

template<typename T>
class Book {
public:
    string title;
    string author;
    string genre;
    bool isTaken;
    T takenById;

    Book() {
        title = "";
        author = "";
        genre = "";
        isTaken = false;
        takenById = T();
    }

    Book(const string& t, const string& a, const string& g) {
        title = t;
        author = a;
        genre = g;
        isTaken = false;
        takenById = T();
    }
};
