#pragma once
#include <string>
using namespace std;

template<typename T>
class Visitor {
public:
    string surname;
    T id;
    int booksOnHand;
    int visitCount;

    Visitor() {
        surname = "";
        id = T();
        booksOnHand = 0;
        visitCount = 0;
    }

    Visitor(const string& s, T idValue) {
        surname = s;
        id = idValue;
        booksOnHand = 0;
        visitCount = 0;
    }
};
