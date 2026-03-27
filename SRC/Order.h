#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include "OrderItem.h"
using namespace std;

//Enumeration for order status
enum class OrderStatus {
    CREATED,
    ASSIGNED,
    IN_PROGRESS,
    COMPLETED
};

//Helper functions to convert OrderStatus to string and from string
string orderStatusToString(OrderStatus status);
OrderStatus stringToOrderStatus(const string& str);

class Order {
private:
    string orderID;
    string customerName;
    vector<OrderItem> items; // Composition: Order owns its items
    OrderStatus status;
    string assignedEmployeeID;

public:
    Order(string id, string customer);

    //Getters
    string getOrderID() const;
    string getCustomerName() const;
    vector<OrderItem> getItems() const;
    OrderStatus getStatus() const;
    string getStatusString() const;
    string getAssignedEmployeeID() const;

    //Setters
    void setStatus(OrderStatus s);
    void setAssignedEmployee(string empID);
    void setCustomerName(string name);

    //Item management
    void addItem(OrderItem item);
    void removeItem(string productID);
    void editItemQuantity(string productID, int newQty);

    //Display
    void display() const;
    void displayDetailed() const;
};

#endif