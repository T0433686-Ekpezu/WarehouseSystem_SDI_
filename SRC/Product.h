#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;


//Product class(represents a single item in the warehouse)
//It demonstrates encapsulation(private data,public getters/setters)
class Product {
    private:
    string productID;
    string name;
    int quantity;
    string location;

    public:
    //constructor
    Product(string id, string name, int qty, string loc);

    //Getter
    string getProductID() const;
    string getName() const;
    string getQuantity() const;
    string getLocation() const;

    //Setter
    void setName(string name);
    void setQuantity(int qty);
    void setLocation(string loc);

    //Display product info
    void display() const;

};

#endif