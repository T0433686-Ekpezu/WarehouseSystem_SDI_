#include "Product.h"
#include <iostream>
#include <iomanip>
using namespace std;

//Constructor(initialises all attributes)
Product::Product(string id, string name, int qty, string loc)
    : productID(id), name(name), quantity(qty), location(loc) {}

//Getters(return private data safely)
string Product::getProductID() const { return productID; }
string Product::getName() const { return name; }
int Product::getQuantity() const { return quantity; }
string Product::getLocation() const { return location; }

//Setters(allow controlled modification)
void Product::setName(string name) { this->name = name; }

void Product::setQuantity(int qty) {
    if (qty >= 0) {
        this->quantity = qty;
    } else {
        cout << "Error: Quantity cannot be negative." << endl;
    }
}

void Product::setLocation(string loc) { this->location = loc; }

//Display formatted product information
void Product::display() const {
    cout << left << setw(12) << productID
         << setw(25) << name
         << setw(10) << quantity
         << setw(15) << location << endl;
}