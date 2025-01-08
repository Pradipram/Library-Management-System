# Library Management System

This is a simple Library Management System implemented in C++. It allows users to register, login, and perform various operations such as searching for books, issuing books, and returning books. The data is stored in a JSON file using the `nlohmann/json` library.

## Features

- User registration and login
- Case-insensitive user IDs
- Search for books
- Issue and return books
- Data stored in a JSON file for easy readability

## Requirements

- C++ compiler (e.g., g++)
- `nlohmann/json` library (included as `json.hpp`)

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/Pradipram/Library-Management-System.git
    cd Library-Management-System
    ```

2. Ensure  is in the project directory.

3. Compile the project:
    ```sh
    g++ -o libraryManagement libraryManagement.cpp
    ```

## Usage

1. Run the executable:
    ```sh
    ./libraryManagement
    ```

2. Follow the on-screen instructions to register, login, and perform various operations.

## File Structure

- : Main source code file
- : JSON library header file
- : JSON file to store user and book data (ignored by )

## Example

```sh
*****************************************
*                                       *
*       Welcome to Pradip Library       *
*                                       *
*****************************************
Select Option: 
0. Exit
1. Register
2. Login
Enter input: 1
Enter your userId: user1
Enter your password: pass1
User Registered Successfully
Press any key to continue . . .