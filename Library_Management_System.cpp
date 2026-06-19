#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

class Book
{
private:
    int bookID;
    string title;
    string author;
    bool issued;

public:
    void addBook()
    {
        cout << "\nEnter Book ID: ";
        cin >> bookID;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        issued = false;
    }

    void displayBook() const
    {
        cout << left << setw(10) << bookID
             << setw(25) << title
             << setw(20) << author
             << setw(10) << (issued ? "Issued" : "Available")
             << endl;
    }

    int getBookID() const
    {
        return bookID;
    }

    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    bool isIssued() const
    {
        return issued;
    }

    void issueBook()
    {
        issued = true;
    }

    void returnBook()
    {
        issued = false;
    }

    void saveToFile(ofstream &file)
    {
        file << bookID << "|"
             << title << "|"
             << author << "|"
             << issued << endl;
    }

    void loadFromFile(string line)
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);

        bookID = stoi(line.substr(0, pos1));
        title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        author = line.substr(pos2 + 1, pos3 - pos2 - 1);
        issued = stoi(line.substr(pos3 + 1));
    }
};

// Add Book
void addBook()
{
    Book b;

    b.addBook();

    ofstream file("library.txt", ios::app);
    b.saveToFile(file);
    file.close();

    cout << "\nBook Added Successfully!\n";
}

// Display Books
void displayBooks()
{
    ifstream file("library.txt");
    string line;

    cout << "\n--------------------------------------------------------------\n";
    cout << left << setw(10) << "ID"
         << setw(25) << "Title"
         << setw(20) << "Author"
         << setw(10) << "Status" << endl;
    cout << "--------------------------------------------------------------\n";

    while (getline(file, line))
    {
        Book b;
        b.loadFromFile(line);
        b.displayBook();
    }

    file.close();
}

// Search by Title
void searchByTitle()
{
    string searchTitle;
    bool found = false;

    cout << "\nEnter Book Title: ";
    cin.ignore();
    getline(cin, searchTitle);

    ifstream file("library.txt");
    string line;

    while (getline(file, line))
    {
        Book b;
        b.loadFromFile(line);

        if (b.getTitle() == searchTitle)
        {
            b.displayBook();
            found = true;
        }
    }

    if (!found)
        cout << "\nBook Not Found!\n";

    file.close();
}

// Search by Author
void searchByAuthor()
{
    string searchAuthor;
    bool found = false;

    cout << "\nEnter Author Name: ";
    cin.ignore();
    getline(cin, searchAuthor);

    ifstream file("library.txt");
    string line;

    while (getline(file, line))
    {
        Book b;
        b.loadFromFile(line);

        if (b.getAuthor() == searchAuthor)
        {
            b.displayBook();
            found = true;
        }
    }

    if (!found)
        cout << "\nNo Books Found!\n";

    file.close();
}

// Issue Book
void issueBook()
{
    int id;
    bool found = false;

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    ifstream file("library.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line))
    {
        Book b;
        b.loadFromFile(line);

        if (b.getBookID() == id)
        {
            if (!b.isIssued())
            {
                b.issueBook();
                cout << "\nBook Issued Successfully!\n";
            }
            else
            {
                cout << "\nBook Already Issued!\n";
            }

            found = true;
        }

        b.saveToFile(temp);
    }

    file.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found)
        cout << "\nBook Not Found!\n";
}

// Return Book
void returnBook()
{
    int id;
    bool found = false;

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    ifstream file("library.txt");
    ofstream temp("temp.txt");

    string line;

    while (getline(file, line))
    {
        Book b;
        b.loadFromFile(line);

        if (b.getBookID() == id)
        {
            if (b.isIssued())
            {
                b.returnBook();
                cout << "\nBook Returned Successfully!\n";
            }
            else
            {
                cout << "\nBook Was Not Issued!\n";
            }

            found = true;
        }

        b.saveToFile(temp);
    }

    file.close();
    temp.close();

    remove("library.txt");
    rename("temp.txt", "library.txt");

    if (!found)
        cout << "\nBook Not Found!\n";
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search by Title\n";
        cout << "4. Search by Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchByTitle();
            break;

        case 4:
            searchByAuthor();
            break;

        case 5:
            issueBook();
            break;

        case 6:
            returnBook();
            break;

        case 7:
            cout << "\nThank You for Using Library Management System!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}