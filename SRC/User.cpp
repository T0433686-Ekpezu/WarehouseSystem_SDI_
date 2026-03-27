#include "User.h"
using namespace std;

User::User(string id, string name, string pw)
    : userID(id), name(name), password(pw) {}

User::~User() {}

string User::getUserID() const { return userID; }
string User::getName() const { return name; }
void User::setName(string name) { this->name = name; }

bool User::verifyPassword(string pw) const {
    return password == pw;
}

string User::getPassword() const {
    return password;
}