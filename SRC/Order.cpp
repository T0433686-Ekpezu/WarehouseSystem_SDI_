#include "Order.h"
#include <iostream>
#include <iomanip>
using namespace std;

//Convert OrderStatus enum to readable string
string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::CREATED:     return "CREATED";
        case OrderStatus::ASSIGNED:    return "ASSIGNED";
        case OrderStatus::IN_PROGRESS: return "IN_PROGRESS";
        case OrderStatus::COMPLETED:   return "COMPLETED";
        default:                       return "UNKNOWN";
    }
}

//Convert string back to OrderStatus
OrderStatus stringToOrderStatus(const string& str) {
    if (str == "ASSIGNED")    return OrderStatus::ASSIGNED;
    if (str == "IN_PROGRESS") return OrderStatus::IN_PROGRESS;
    if (str == "COMPLETED")   return OrderStatus::COMPLETED;
    return OrderStatus::CREATED;
}

//Constructor
Order::Order(string id, string customer)
    : orderID(id), customerName(customer), status(OrderStatus::CREATED), assignedEmployeeID("") {}

//Getters
string Order::getOrderID() const { return orderID; }
string Order::getCustomerName() const { return customerName; }
vector<OrderItem> Order::getItems() const { return items; }
OrderStatus Order::getStatus() const { return status; }
string Order::getStatusString() const { return orderStatusToString(status); }
string Order::getAssignedEmployeeID() const { return assignedEmployeeID; }

//Setters
void Order::setStatus(OrderStatus s) { status = s; }
void Order::setAssignedEmployee(string empID) { assignedEmployeeID = empID; }
void Order::setCustomerName(string name) { customerName = name; }

//Add an item to the order
void Order::addItem(OrderItem item) {
    items.push_back(item);
}

//Remove an item by product ID
void Order::removeItem(string productID) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->getProductID() == productID) {
            items.erase(it);
            cout << "Item " << productID << " removed from order." << endl;
            return;
        }
    }
    cout << "Error: Product " << productID << " not found in this order." << endl;
}

//Edit the quantity of an item in the order
void Order::editItemQuantity(string productID, int newQty) {
    for (auto& item : items) {
        if (item.getProductID() == productID) {
            item.setQuantity(newQty);
            cout << "Quantity updated for " << productID << "." << endl;
            return;
        }
    }
    cout << "Error: Product " << productID << " not found in this order." << endl;
}

//Display summary
void Order::display() const {
    cout << left << setw(12) << orderID
         << setw(20) << customerName
         << setw(14) << orderStatusToString(status)
         << setw(12) << assignedEmployeeID
         << items.size() << " items" << endl;
}

//Display full order with all items
void Order::displayDetailed() const {
    cout << "\n========================================" << endl;
    cout << "Order ID:    " << orderID << endl;
    cout << "Customer:    " << customerName << endl;
    cout << "Status:      " << orderStatusToString(status) << endl;
    cout << "Assigned To: " << (assignedEmployeeID.empty() ? "Unassigned" : assignedEmployeeID) << endl;
    cout << "----------------------------------------" << endl;
    cout << "    " << left << setw(12) << "Product ID"
         << setw(25) << "Product Name"
         << setw(8) << "Qty" << endl;
    cout << "    " << string(45, '-') << endl;
    for (const auto& item : items) {
        item.display();
    }
    cout << "========================================\n" << endl;
}