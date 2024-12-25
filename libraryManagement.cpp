#include <bits/stdc++.h>
using namespace std;
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

class Book{
    string BookId;
    string Title;
    string publication;
    string author;
    int availableBook;
};

class Library{
    unordered_map<string,User> users;
    unordered_map<string,Book> shelf;
    bool isAlreadyPresent(string);
    void saveusersToFile();
    void loadUsersFromFile();

    public:
    Library(){
        loadUsersFromFile();
    }
    void Register();
    void Login();
};

bool Library::isAlreadyPresent(string userId){
    userId = toLowerCase(userId);
    return users.find(userId) != users.end();
}

void Library::saveusersToFile(){
    ofstream file;
    file.open("users.txt");
    for(auto it = users.begin();it!=users.end();it++){
        file<<it->first<<" "<<it->second.password<<endl;
    }
    file.close();
}

void Library::loadUsersFromFile(){
    ifstream file;
    file.open("users.txt");
    string userId,password;
    while(file>>userId>>password){
        User u(userId,password);
        users[toLowerCase(userId)] = u;
    }
    file.close();
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
        User u(userId,password);
        users[userId] = u;
        saveusersToFile();
        cout<<"User Registered Successfully"<<endl;
    }
}

void Library::Login(){
    cout<<"Enter you userId: ";
    string userId;cin>>userId;
    userId = toLowerCase(userId);
    cout<<"Enter your password: ";
    string password;cin>>password;
    bool isPresent = isAlreadyPresent(userId);
    if(isPresent){
        User u = users[userId];
        if(u.password == password){
            cout<<"Login Successfull"<<endl;
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
