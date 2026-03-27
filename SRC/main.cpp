#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "Product.h"
#include "OrderItem.h"
#include "Order.h"
#include "Inventory.h"
#include "Employee.h"
#include "Manager.h"
#include "FileHandler.h"
using namespace std;

//Function prototypes
void managerSession(Manager& manager, Inventory& inv,
                    vector<Employee>& employees, vector<Order>& orders,
                    FileHandler& fileHandler);
void employeeSession(Employee& employee, Inventory& inv,
                     vector<Order>& orders, FileHandler& fileHandler);
int getValidChoice(int min, int max);

//MAIN FUNCTION
int main() {
    //Initialise file handler and load data
    FileHandler fileHandler("products.csv", "employees.csv", "orders.csv");

    //Load all data from files
    cout << "========================================" << endl;
    cout << " WAREHOUSE INVENTORY MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "\nLoading data..." << endl;

    Inventory inventory;
    vector<Product> loadedProducts = fileHandler.loadProducts();
    for (auto& p : loadedProducts) {
        inventory.addProduct(p);
    }

    vector<Employee> employees;
    fileHandler.loadEmployees(employees);

    vector<Order> orders = fileHandler.loadOrders();

    //Create default manager if none exists
    Manager manager("M001", "Admin", "admin123");

    cout << "\nSystem ready.\n" << endl;

    //MAIN LOOP
    bool running = true;
    while (running) {
        cout << "\n========================================" << endl;
        cout << "          MAIN LOGIN SCREEN" << endl;
        cout << "========================================" << endl;
        cout << "1. Login as Manager" << endl;
        cout << "2. Login as Employee" << endl;
        cout << "3. Exit System" << endl;
        cout << "========================================" << endl;
        cout << "Enter choice: ";

        int choice = getValidChoice(1, 3);

        switch (choice) {
            case 1: {
                //Manager login
                string pw;
                cout << "Enter Manager Password: ";
                getline(cin, pw);

                if (manager.verifyPassword(pw)) {
                    cout << "\nLogin successful!" << endl;
                    managerSession(manager, inventory, employees, orders, fileHandler);
                } else {
                    cout << "Error: Incorrect password." << endl;
                }
                break;
            }
            case 2: {
                //Employee login
                string empID, pw;
                cout << "Enter Employee ID: ";
                getline(cin, empID);
                cout << "Enter Password: ";
                getline(cin, pw);

                bool found = false;
                for (auto& emp : employees) {
                    if (emp.getUserID() == empID) {
                        found = true;
                        if (emp.verifyPassword(pw)) {
                            cout << "\nLogin successful!" << endl;
                            employeeSession(emp, inventory, orders, fileHandler);
                        } else {
                            cout << "Error: Incorrect password." << endl;
                        }
                        break;
                    }
                }
                if (!found) {
                    cout << "Error: Employee ID not found." << endl;
                }
                break;
            }
            case 3: {
                //Save all data before exit
                cout << "\nSaving data..." << endl;
                fileHandler.saveProducts(inventory.getAllProducts());
                fileHandler.saveEmployees(employees);
                fileHandler.saveOrders(orders);
                cout << "All data saved. Goodbye!" << endl;
                running = false;
                break;
            }
        }
    }

    return 0;
}

//MANAGER SESSION
void managerSession(Manager& manager, Inventory& inv,
                    vector<Employee>& employees, vector<Order>& orders,
                    FileHandler& fileHandler) {
    bool loggedIn = true;

    while (loggedIn) {
        manager.showMenu();
        int choice = getValidChoice(1, 14);

        switch (choice) {
            case 1:
                manager.addProduct(inv);
                fileHandler.saveProducts(inv.getAllProducts()); //Save after change
                break;
            case 2:
                manager.viewProducts(inv);
                break;
            case 3:
                manager.editProduct(inv);
                fileHandler.saveProducts(inv.getAllProducts());
                break;
            case 4:
                manager.addEmployee(employees);
                fileHandler.saveEmployees(employees);
                break;
            case 5:
                manager.viewEmployees(employees);
                break;
            case 6:
                manager.editEmployee(employees);
                fileHandler.saveEmployees(employees);
                break;
            case 7:
                manager.createOrder(orders, inv);
                fileHandler.saveOrders(orders);
                break;
            case 8:
                manager.viewOrders(orders);
                break;
            case 9:
                manager.editOrder(orders);
                fileHandler.saveOrders(orders);
                break;
            case 10:
                manager.assignOrder(orders, employees, inv);
                fileHandler.saveOrders(orders);
                fileHandler.saveEmployees(employees);
                break;
            case 11:
                manager.generateInventoryReport(inv);
                break;
            case 12:
                manager.generateCompletedOrdersReport(orders);
                break;
            case 13:
                manager.generatePendingOrdersReport(orders);
                break;
            case 14:
                cout << "Logging out..." << endl;
                loggedIn = false;
                break;
        }
    }
}

//EMPLOYEE SESSION
void employeeSession(Employee& employee, Inventory& inv,
                     vector<Order>& orders, FileHandler& fileHandler) {
    bool loggedIn = true;

    while (loggedIn) {
        employee.showMenu();
        int choice = getValidChoice(1, 5);

        switch (choice) {
            case 1:
                employee.viewAssignedOrders(orders);
                break;
            case 2:
                employee.searchProduct(inv);
                break;
            case 3: {
                cout << "Enter Order ID to complete: ";
                string orderID;
                getline(cin, orderID);

                for (auto& order : orders) {
                    if (order.getOrderID() == orderID) {
                        if (employee.completeOrder(order, inv)) {
                            // Save after completing (FR-27)
                            fileHandler.saveOrders(orders);
                            fileHandler.saveProducts(inv.getAllProducts());
                        }
                        break;
                    }
                }
                break;
            }
            case 4:
                employee.generateEmployeeReport(orders);
                break;
            case 5:
                cout << "Logging out..." << endl;
                loggedIn = false;
                break;
        }
    }
}

//INPUT VALIDATION HELPER
int getValidChoice(int min, int max) {
    int choice;
    while (true) {
        if (cin >> choice && choice >= min && choice <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cout << "Invalid input. Please enter a number between "
             << min << " and " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}