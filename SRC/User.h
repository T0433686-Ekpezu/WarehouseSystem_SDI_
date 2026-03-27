#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string userID;
    string name;
    string password;

public:
    User(string id, string name, string pw);
    virtual ~User();//Virtual destructor for proper cleanup of derived classes

    //Getters
    string getUserID() const;
    string getName() const;

    //Setters
    void setName(string name);

    //Password access
    bool verifyPassword(string pw) const;
    string getPassword() const; //Needed for file persistence

    virtual void showMenu() = 0;
};

#endif