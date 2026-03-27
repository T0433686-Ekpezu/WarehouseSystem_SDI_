#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include "User.h"
#include "Order.h"
#include "Inventory.h"
using namespace std;


class Employee : public User {
private:
    vector<string> assignedOrders; //List of order IDs assigned to this employee

public:
    Employee(string id, string name, string pw);

    //Override abstract method from User
    void showMenu() override;

    //Employee-specific operations
    void viewAssignedOrders(const vector<Order>& orders);
    void searchProduct(Inventory& inv);
    bool completeOrder(Order& order, Inventory& inv);

    //Assigned orders management
    vector<string> getAssignedOrders() const;
    void addAssignedOrder(string orderID);
    void removeAssignedOrder(string orderID);

    //Report generation
    void generateEmployeeReport(const vector<Order>& orders);
};

#endif