#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <string>
using namespace std;

class OrderItem {
private:
    string productID;
    string productName;
    int quantity;

public:
    OrderItem(string prodID, string prodName, int qty);

    string getProductID() const;
    string getProductName() const;
    int getQuantity() const;
    void setQuantity(int qty);

    void display() const;
};

#endif