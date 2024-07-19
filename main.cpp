#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>
#include <locale>

struct Book {
    int id;
    std::string title;
    std::string author;
    bool isIssued;
    std::string issuedTo;
};

void addBook(std::vector<Book>& books, int id, const std::string& title, const std::string& author) {
    books.push_back({id, title, author, false, ""});
}

bool icompare(const std::string& a, const std::string& b) {
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), [](char a, char b) {
        return std::tolower(a) == std::tolower(b);
    });
}

Book* searchBookById(std::vector<Book>& books, int id) {
    for (auto& book : books) {
        if (book.id == id) {
            return &book;
        }
    }
    return nullptr;
}

Book* searchBookByTitle(std::vector<Book>& books, const std::string& title) {
    for (auto& book : books) {
        if (icompare(book.title, title)) {
            return &book;
        }
    }
    return nullptr;
}

void issueBook(Book& book, const std::string& studentName) {
    if (!book.isIssued) {
        book.isIssued = true;
        book.issuedTo = studentName;
        std::cout << "Book issued to " << studentName << std::endl;
    } else {
        std::cout << "Book already issued to " << book.issuedTo << std::endl;
    }
}

void returnBook(Book& book) {
    if (book.isIssued) {
        book.isIssued = false;
        book.issuedTo = "";
        std::cout << "Book returned." << std::endl;
    } else {
        std::cout << "Book was not issued." << std::endl;
    }
}

void listBooks(const std::vector<Book>& books) {
    for (const auto& book : books) {
        std::cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                  << ", Status: " << (book.isIssued ? "Issued to " + book.issuedTo : "Available") << std::endl;
    }
}

void deleteBook(std::vector<Book>& books, int id) {
    auto it = std::remove_if(books.begin(), books.end(), [id](Book& book) { return book.id == id; });
    if (it != books.end()) {
        books.erase(it, books.end());
        std::cout << "Book deleted." << std::endl;
    } else {
        std::cout << "Book not found." << std::endl;
    }
}

void sortBooksById(std::vector<Book>& books) {
    std::sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.id < b.id;
    });
}

void sortBooksByTitle(std::vector<Book>& books) {
    std::sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.title < b.title;
    });
}

int main() {
    std::vector<Book> books;
    int choice, id;
    std::string title, author, studentName;

    while (true) {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Search Book by ID\n";
        std::cout << "3. Search Book by Title\n";
        std::cout << "4. Issue Book\n";
        std::cout << "5. Return Book\n";
        std::cout << "6. List All Books\n";
        std::cout << "7. Delete Book\n";
        std::cout << "8. Sort Books by ID\n";
        std::cout << "9. Sort Books by Title\n";
        std::cout << "10. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter Book ID: ";
                std::cin >> id;
                std::cin.ignore();
                std::cout << "Enter Book Title: ";
                std::getline(std::cin, title);
                std::cout << "Enter Book Author: ";
                std::getline(std::cin, author);
                addBook(books, id, title, author);
                std::cout << "Book added successfully.\n";
                break;
            case 2:
                std::cout << "Enter Book ID: ";
                std::cin >> id;
                if (Book* book = searchBookById(books, id)) {
                    std::cout << "Book Found: ID: " << book->id << ", Title: " << book->title
                              << ", Author: " << book->author << ", Status: "
                              << (book->isIssued ? "Issued to " + book->issuedTo : "Available") << std::endl;
                } else {
                    std::cout << "Book not found.\n";
                }
                break;
            case 3:
                std::cout << "Enter Book Title: ";
                std::cin.ignore(); 
                std::getline(std::cin, title);
                if (Book* book = searchBookByTitle(books, title)) {
                    std::cout << "Book Found: ID: " << book->id << ", Title: " << book->title
                              << ", Author: " << book->author << ", Status: "
                              << (book->isIssued ? "Issued to " + book->issuedTo : "Available") << std::endl;
                } else {
                    std::cout << "Book not found.\n";
                }
                break;
            case 4:
                std::cout << "Enter Book ID: ";
                std::cin >> id;
                std::cin.ignore(); 
                if (Book* book = searchBookById(books, id)) {
                    std::cout << "Enter Student Name: ";
                    std::getline(std::cin, studentName);
                    issueBook(*book, studentName);
                } else {
                    std::cout << "Book not found.\n";
                }
                break;
            case 5:
                std::cout << "Enter Book ID: ";
                std::cin >> id;
                if (Book* book = searchBookById(books, id)) {
                    returnBook(*book);
                } else {
                    std::cout << "Book not found.\n";
                }
                break;
            case 6:
                listBooks(books);
                break;
            case 7:
                std::cout << "Enter Book ID: ";
                std::cin >> id;
                deleteBook(books, id);
                break;
            case 8:
                sortBooksById(books);
                std::cout << "Books sorted by ID.\n";
                break;
            case 9:
                sortBooksByTitle(books);
                std::cout << "Books sorted by Title.\n";
                break;
            case 10:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
