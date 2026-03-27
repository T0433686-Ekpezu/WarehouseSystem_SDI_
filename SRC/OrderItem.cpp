#include "OrderItem.h"
#include <iostream>
#include <iomanip>
using namespace std;

OrderItem::OrderItem(string prodID, string prodName, int qty)
    : productID(prodID), productName(prodName), quantity(qty) {}

string OrderItem::getProductID() const { return productID; }
string OrderItem::getProductName() const { return productName; }
int OrderItem::getQuantity() const { return quantity; }
void OrderItem::setQuantity(int qty) { this->quantity = qty; }

void OrderItem::display() const {
    cout << "    " << left << setw(12) << productID
         << setw(25) << productName
         << setw(8) << quantity << endl;
}