#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "Product.h"
#include "OrderItem.h"
using namespace std;

class Inventory {
private:
    vector<Product> products; //Composition(Inventory owns Products)

public:
    //Product management
    void addProduct(Product p);
    Product* findProductByID(string id);
    Product* findProductByName(string name);
    void editProduct(string id);
    vector<Product>& getAllProducts();

    //Stock operations
    bool checkStock(const vector<OrderItem>& items);
    void deductStock(string productID, int qty);

    //Sorting
    void sortByID();
    void sortByName();
    void sortByQuantity();

    //Display
    void displayAll() const;
    int getProductCount() const;
    bool productExists(string id) const;
};

#endif