#include <iostream>
#include "Library.h"
#include "Book.h"
#include "Visitor.h"
using namespace std;

int main() {
    Library<int> lib(5, 3);

    lib.addBook("Harry Potter", "J.K. Rowling", "Fantasy");
    lib.addBook("Odissea", "Gomer", "Mif");

    lib.addVisitor("Ivanov", 101);
    lib.addVisitor("Petrov", 102);

    lib.printAllBooks();

    cout << "Give Harry Potter to visitor 101: " 
         << (lib.giveBook("Harry Potter", 101) ? "Success" : "Fail") << endl;

    lib.printAllBooks();

    lib.returnBook("Harry Potter", 101);
    lib.printAllBooks();

    return 0;
}
