#include <bits/stdc++.h>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;
#define Padding "\t\t\t\t\t"
#define cout cout<<Padding

enum userType {NORMAL, ADMIN,OTHER};

string toLowerCase(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

class User{
    public:
    string userId;
    string password;
    userType typeOfUser;

    User(){}

    User(string userId,string password){
        this->userId = userId;
        this->password = password;
        this->typeOfUser = NORMAL;
    }
};

class NormalUser:public User{
    public:
    vector<string> booksIssued;
    NormalUser(){}
    NormalUser(string userId,string password){
        this->userId = userId;
        this->password = password;
        this->typeOfUser = NORMAL;
    }
};

class Admin:public User{
    public:
    Admin(){}
    Admin(string userId,string password){
        this->userId = userId;
        this->password = password;
        this->typeOfUser = ADMIN;
    }
};

class Book{
    public:
    string BookId;
    string Title;
    string publication;
    string author;
    int availableBook;

    Book(){}
    Book(string BookId,string Title,string publication,string author,int availableBook = 0){
        this->BookId = BookId;
        this->Title = Title;
        this->publication = publication;
        this->author = author;
        this->availableBook = availableBook;
    }
};

class Library{
    unordered_map<string,NormalUser> users;
    unordered_map<string,Admin> admins;
    unordered_map<string,Book> shelf;
    bool isAlreadyPresent(string);
    void loadUsersFromFile();
    void NormalUserOperations(string);
    void AdminOperations();

    public:
    Library(){
        loadUsersFromFile();
    }
    void saveusersToFile();
    void Register();
    void Login();
};

void Library::NormalUserOperations(string userId){
    while(1){
        cout<<"Normal User Operations"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"1. Search Book"<<endl;
        cout<<"2. Issue Book"<<endl;
        cout<<"3. Return Book"<<endl;
        cout<<"Enter input: ";
        int option;cin>>option;
        if(option == 0){
            break;
        }
        else if(option == 1){
            cout<<"Enter BookId: ";
            string BookId;cin>>BookId;
            bool isPresent = shelf.find(BookId) != shelf.end();
            if(isPresent){
                Book b = shelf[BookId];
                cout<<"BookId: "<<b.BookId<<endl;
                cout<<"Title: "<<b.Title<<endl;
                cout<<"Publication: "<<b.publication<<endl;
                cout<<"Author: "<<b.author<<endl;
                cout<<"Available Book: "<<b.availableBook<<endl;
            }
            else{
                cout<<"Book not present"<<endl;
            }
        }
        else if(option == 2){
            cout<<"Enter BookId: ";
            string BookId;cin>>BookId;
            bool isPresent = shelf.find(BookId) != shelf.end();
            if(isPresent){
                Book &b = shelf[BookId];
                if(b.availableBook > 0){
                    b.availableBook--;
                    users[userId].booksIssued.push_back(BookId);
                    cout<<"Book Issued Successfully"<<endl;
                }
                else{
                    cout<<"Book not available"<<endl;
                }
            }
            else{
                cout<<"Book not present"<<endl;
            }
        }
        else if(option == 3){
            cout<<"Enter BookId: ";
            string BookId;cin>>BookId;
            bool isPresent = shelf.find(BookId) != shelf.end();
            if(isPresent){
                Book &b = shelf[BookId];
                b.availableBook++;
                users[userId].booksIssued.pop_back();
                cout<<"Book Returned Successfully"<<endl;
            }
            else{
                cout<<"This book has been removed from the library."<<endl;
            }
        }
        else{
            cout<<"Invalid Input"<<endl;
        }
        system("pause");
    }
}

void Library::AdminOperations(){
    while(1){
        cout<<"Admin Operations"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"1. Add Book"<<endl;
        cout<<"2. Remove Book"<<endl;
        cout<<"3. Update Book"<<endl;
        cout<<"Enter input: ";
        int option;cin>>option;
        if(option == 0){
            return;
        }
        else if(option == 1){
            cout<<"Enter BookId: ";
            string BookId;cin>>BookId;
            bool isPresent = shelf.find(BookId) != shelf.end();
            if(isPresent){
                cout<<"This book already present"<<endl;
                cout<<"Enter amount of book to add: ";
                int amount;cin>>amount;
                shelf[BookId].availableBook += amount;
                cout<<"Book added successfully"<<endl;
            }
            else{
                cout<<"This is a new book"<<endl;
                cout<<"Enter Title: "; 
                string Title;
                getline(cin>>ws,Title);
                cout<<"Enter Publication: ";
                string publication;
                getline(cin,publication);
                cout<<"Enter Author: ";
                string author;
                getline(cin,author);
                cout<<"Enter amount of book to add: ";
                int amount;cin>>amount;
                Book b(BookId,Title,publication,author,amount);
                shelf[BookId] = b;
                cout<<"Book added successfully"<<endl;
            }
        }
        else if(option == 2){
            cout<<"Enter BookId: ";
            string BookId;cin>>BookId;
            bool isPresent = shelf.find(BookId) != shelf.end();
            if(isPresent){
                shelf.erase(BookId);
            }
            else{
                cout<<"This book is not present"<<endl;
            }
        }
        else if(option == 3){
            cout<<"Enter BookId: ";
            string BookId;cin>>BookId;
            bool isPresent = shelf.find(BookId) != shelf.end();
            if(isPresent){
                cout<<"Enter Title: "; 
                string Title;cin>>Title;
                cout<<"Enter Publication: ";
                string publication;
                getline(cin>>ws,publication);
                cout<<"Enter Author: ";
                string author;
                getline(cin,author);
                shelf[BookId].Title = Title;
                shelf[BookId].publication = publication;
                shelf[BookId].author = author;
                cout<<"Book updated successfully"<<endl;
            }
            else{
                cout<<"This book is not present"<<endl;
            }
        }
        else{
            cout<<"Invalid Input"<<endl;
        }
        system("pause");
    }
}

bool Library::isAlreadyPresent(string userId){
    userId = toLowerCase(userId);
    return users.find(userId) != users.end();
}

void Library::saveusersToFile() {
    json j;
    j["users"] = json::array();
    for (const auto& pair : users) {
        j["users"].push_back({
            {"userId", pair.first},
            {"password", pair.second.password},
            {"booksIssued", pair.second.booksIssued}
        });
    }
    j["shelf"] = json::array();
    for (const auto& pair : shelf) {
        j["shelf"].push_back({
            {"BookId", pair.first},
            {"Title", pair.second.Title},
            {"publication", pair.second.publication},
            {"author", pair.second.author},
            {"availableBook", pair.second.availableBook}
        });
    }
    j["admins"] = json::array();
    Admin a = Admin("admin","admin");
    admins["admin"] = a;
    for (const auto& pair : admins) {
        j["admins"].push_back({
            {"userId", pair.first},
            {"password", pair.second.password}
        });
    }
    ofstream file("library.json");
    file << j.dump(4); // Pretty print with 4 spaces
    file.close();
}

void Library::loadUsersFromFile() {
    ifstream file("library.json");
    if (file.is_open()) {
        json j;
        file >> j;
        for (const auto& element : j["users"]) {
            string userId = element["userId"];
            string password = element["password"];
            vector<string> booksIssued = element["booksIssued"];
            NormalUser u(userId, password);
            u.booksIssued = booksIssued;
            users[toLowerCase(userId)] = u;
        }
        for (const auto& element : j["shelf"]) {
            string bookId = element["BookId"];
            Book b;
            b.BookId = bookId;
            b.Title = element["Title"];
            b.publication = element["publication"];
            b.author = element["author"];
            b.availableBook = element["availableBook"];
            shelf[bookId] = b;
        }
        for(const auto& element : j["admins"]){
            string userId = element["userId"];
            string password = element["password"];
            Admin a(userId,password);
            admins[userId] = a;
        }
        file.close();
    }
}

void Library::Register(){
    cout<<"Enter you userId: ";
    string userId;cin>>userId;
    userId = toLowerCase(userId);
    cout<<"Enter your password: ";
    string password;cin>>password;
    bool isPresent = isAlreadyPresent(userId);
    if(isPresent){
        cout<<"User already present"<<endl;
    }
    else{
        NormalUser u(userId,password);
        users[userId] = u;
        // saveusersToFile();
        cout<<"User Registered Successfully"<<endl;
        //do the normal user operations
        NormalUserOperations(userId);
    }
}

void Library::Login(){
    cout<<"Enter you userId: ";
    string userId;cin>>userId;
    userId = toLowerCase(userId);
    cout<<"Enter your password: ";
    string password;cin>>password;
    bool isadmin = admins.find(userId) != admins.end();
    if(isadmin){
        AdminOperations();
        return;
    }
    bool isPresent = isAlreadyPresent(userId);
    if(isPresent){
        User u = users[userId];
        if(u.password == password){
            cout<<"Login Successfull"<<endl;
            NormalUserOperations(userId);
        }
        else{
            cout<<"Invalid Password"<<endl;
        }
    }
    else{
        cout<<"User not present"<<endl;
    }
}

int main() {
    Library l;
    while(1){
        cout<<"*****************************************"<<endl;
        cout<<"*"<<Padding<<"*"<<endl;
        cout<<"*\tWelcom to Pradip Library\t*"<<endl;
        cout<<"*"<<Padding<<"*"<<endl;
        cout<<"*****************************************"<<endl;
        cout<<"Select Option: "<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"1. Register"<<endl;
        cout<<"2. Login"<<endl;
        cout<<"Enter input: ";
        int option;cin>>option;
        if(option == 0){
            l.saveusersToFile();
            break;
        }
        else if(option == 1){
            l.Register();
        }
        else if(option == 2){
            l.Login();
        }
        system("pause");
    }
    return 0;
}
