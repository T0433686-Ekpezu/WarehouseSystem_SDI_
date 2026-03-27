#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <vector>
#include "User.h"
#include "Order.h"
#include "Inventory.h"
#include "Employee.h"
using namespace std;

class Manager : public User {
public:
    Manager(string id, string name, string pw);

    //Override abstract method from User
    void showMenu() override;

    //Product management
    void addProduct(Inventory& inv);
    void viewProducts(Inventory& inv);
    void editProduct(Inventory& inv);

    //Employee management
    void addEmployee(vector<Employee>& employees);
    void viewEmployees(const vector<Employee>& employees);
    void editEmployee(vector<Employee>& employees);

    //Order management
    void createOrder(vector<Order>& orders, Inventory& inv);
    void editOrder(vector<Order>& orders);
    void viewOrders(const vector<Order>& orders);
    void assignOrder(vector<Order>& orders, vector<Employee>& employees, Inventory& inv);

    //Report generation
    void generateInventoryReport(Inventory& inv);
    void generateCompletedOrdersReport(const vector<Order>& orders);
    void generatePendingOrdersReport(const vector<Order>& orders);
};

#endif