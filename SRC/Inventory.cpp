#include "Inventory.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

//Add a product to the inventory
void Inventory::addProduct(Product p) {
    products.push_back(p);
}

//Search by product ID-returns pointer(nullptr if not found)
Product* Inventory::findProductByID(string id) {
    // Using STL find_if with a lambda function
    auto it = find_if(products.begin(), products.end(),
        [&id](const Product& p) { return p.getProductID() == id; });

    if (it != products.end()) {
        return &(*it);  //Return pointer to found product
    }
    return nullptr;
}

//Search by product name(partial match)-returns pointer
Product* Inventory::findProductByName(string name) {
    // Convert search term to lowercase for case-insensitive search
    string searchLower = name;
    transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

    for (auto& p : products) {
        string prodNameLower = p.getName();
        transform(prodNameLower.begin(), prodNameLower.end(), prodNameLower.begin(), ::tolower);
        if (prodNameLower.find(searchLower) != string::npos) {
            return &p;
        }
    }
    return nullptr;
}

//Edit a product by ID
void Inventory::editProduct(string id) {
    Product* p = findProductByID(id);
    if (p == nullptr) {
        cout << "Error: Product " << id << " not found." << endl;
        return;
    }

    cout << "\nEditing Product: " << p->getName() << " (" << id << ")" << endl;
    cout << "1. Edit Name" << endl;
    cout << "2. Edit Quantity" << endl;
    cout << "3. Edit Location" << endl;
    cout << "4. Cancel" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: {
            string newName;
            cout << "Enter new name: ";
            getline(cin, newName);
            if (!newName.empty()) {
                p->setName(newName);
                cout << "Name updated successfully." << endl;
            }
            break;
        }
        case 2: {
            int newQty;
            cout << "Enter new quantity: ";
            cin >> newQty;
            cin.ignore();
            if (newQty >= 0) {
                p->setQuantity(newQty);
                cout << "Quantity updated successfully." << endl;
            } else {
                cout << "Error: Quantity cannot be negative." << endl;
            }
            break;
        }
        case 3: {
            string newLoc;
            cout << "Enter new location: ";
            getline(cin, newLoc);
            if (!newLoc.empty()) {
                p->setLocation(newLoc);
                cout << "Location updated successfully." << endl;
            }
            break;
        }
        case 4:
            cout << "Edit cancelled." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}

//Get reference to all products
vector<Product>& Inventory::getAllProducts() {
    return products;
}

//Check if all items in an order have sufficient stock
bool Inventory::checkStock(const vector<OrderItem>& items) {
    for (const auto& item : items) {
        Product* p = findProductByID(item.getProductID());
        if (p == nullptr) {
            cout << "Error: Product " << item.getProductID() << " not found in inventory." << endl;
            return false;
        }
        if (p->getQuantity() < item.getQuantity()) {
            cout << "Insufficient stock for " << p->getName()
                 << ": need " << item.getQuantity()
                 << ", have " << p->getQuantity() << endl;
            return false;
        }
    }
    return true;
}

//Deduct stock for a product
void Inventory::deductStock(string productID, int qty) {
    Product* p = findProductByID(productID);
    if (p != nullptr) {
        int newQty = p->getQuantity() - qty;
        p->setQuantity(newQty);
        cout << "Stock deducted: " << p->getName()
             << " (" << p->getQuantity() + qty << " -> " << newQty << ")" << endl;
    }
}

//Sort products by ID using STL sort
void Inventory::sortByID() {
    sort(products.begin(), products.end(),
        [](const Product& a, const Product& b) {
            return a.getProductID() < b.getProductID();
        });
    cout << "Products sorted by ID." << endl;
}

//Sort products by name using STL sort
void Inventory::sortByName() {
    sort(products.begin(), products.end(),
        [](const Product& a, const Product& b) {
            return a.getName() < b.getName();
        });
    cout << "Products sorted by name." << endl;
}

//Sort products by quantity using STL sort
void Inventory::sortByQuantity() {
    sort(products.begin(), products.end(),
        [](const Product& a, const Product& b) {
            return a.getQuantity() > b.getQuantity();  // Descending
        });
    cout << "Products sorted by quantity (highest first)." << endl;
}

//Display all products in a formatted table
void Inventory::displayAll() const {
    if (products.empty()) {
        cout << "\nNo products in inventory." << endl;
        return;
    }
    cout << "\n" << left << setw(12) << "Product ID"
         << setw(25) << "Name"
         << setw(10) << "Quantity"
         << setw(15) << "Location" << endl;
    cout << string(62, '-') << endl;
    for (const auto& p : products) {
        p.display();
    }
    cout << "\nTotal products: " << products.size() << endl;
}

int Inventory::getProductCount() const {
    return products.size();
}

bool Inventory::productExists(string id) const {
    for (const auto& p : products) {
        if (p.getProductID() == id) return true;
    }
    return false;
}