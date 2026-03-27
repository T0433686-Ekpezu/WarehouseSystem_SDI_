#include "Employee.h"
#include <iostream>
#include <iomanip>
using namespace std;

Employee::Employee(string id, string name, string pw)
    : User(id, name, pw) {}

//Override showMenu from User
void Employee::showMenu() {
    cout << "\n======================================" << endl;
    cout << "   EMPLOYEE MENU - Welcome " << name << endl;
    cout << "======================================" << endl;
    cout << "1. View Assigned Orders" << endl;
    cout << "2. Search Product" << endl;
    cout << "3. Complete an Order" << endl;
    cout << "4. Generate My Report" << endl;
    cout << "5. Logout" << endl;
    cout << "======================================" << endl;
    cout << "Enter choice: ";
}

//View all orders assigned to this employee (FR-21)
void Employee::viewAssignedOrders(const vector<Order>& orders) {
    cout << "\n--- Orders Assigned to " << name << " ---" << endl;
    bool found = false;

    cout << left << setw(12) << "Order ID"
         << setw(20) << "Customer"
         << setw(14) << "Status"
         << "Items" << endl;
    cout << string(55, '-') << endl;

    for (const auto& order : orders) {
        if (order.getAssignedEmployeeID() == userID) {
            order.display();
            found = true;
        }
    }

    if (!found) {
        cout << "No orders currently assigned to you." << endl;
    }
}

//Search for a product by name or ID (FR-22 - Advanced Feature)
void Employee::searchProduct(Inventory& inv) {
    cout << "\n--- Search Product ---" << endl;
    cout << "1. Search by Product ID" << endl;
    cout << "2. Search by Product Name" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    string searchTerm;
    Product* result = nullptr;

    switch (choice) {
        case 1:
            cout << "Enter Product ID: ";
            getline(cin, searchTerm);
            result = inv.findProductByID(searchTerm);
            break;
        case 2:
            cout << "Enter Product Name (or part of name): ";
            getline(cin, searchTerm);
            result = inv.findProductByName(searchTerm);
            break;
        default:
            cout << "Invalid choice." << endl;
            return;
    }

    if (result != nullptr) {
        cout << "\nProduct Found:" << endl;
        cout << left << setw(12) << "Product ID"
             << setw(25) << "Name"
             << setw(10) << "Quantity"
             << setw(15) << "Location" << endl;
        cout << string(62, '-') << endl;
        result->display();
    } else {
        cout << "Product not found." << endl;
    }
}

//Complete an order - mark as done and deduct stock (FR-23, FR-17)
bool Employee::completeOrder(Order& order, Inventory& inv) {
    //Verify this order is assigned to this employee
    if (order.getAssignedEmployeeID() != userID) {
        cout << "Error: This order is not assigned to you." << endl;
        return false;
    }

    //Verify order is in ASSIGNED or IN_PROGRESS status
    if (order.getStatus() != OrderStatus::ASSIGNED &&
        order.getStatus() != OrderStatus::IN_PROGRESS) {
        cout << "Error: Order cannot be completed (current status: "
             << order.getStatusString() << ")." << endl;
        return false;
    }

    //Check stock is still sufficient before completing
    if (!inv.checkStock(order.getItems())) {
        cout << "Error: Insufficient stock to complete this order." << endl;
        return false;
    }

    //Deduct stock for each item in the order
    cout << "\nDeducting stock for order " << order.getOrderID() << ":" << endl;
    for (const auto& item : order.getItems()) {
        inv.deductStock(item.getProductID(), item.getQuantity());
    }

    //Update order status to "COMPLETED"
    order.setStatus(OrderStatus::COMPLETED);
    cout << "\nOrder " << order.getOrderID() << " completed successfully!" << endl;
    return true;
}

//Get assigned order IDs
vector<string> Employee::getAssignedOrders() const {
    return assignedOrders;
}

//Add an order to assigned list
void Employee::addAssignedOrder(string orderID) {
    assignedOrders.push_back(orderID);
}

//Remove an order from assigned list
void Employee::removeAssignedOrder(string orderID) {
    for (auto it = assignedOrders.begin(); it != assignedOrders.end(); ++it) {
        if (*it == orderID) {
            assignedOrders.erase(it);
            return;
        }
    }
}

//Generate report of employee's orders (FR-24 - Advanced Feature)
void Employee::generateEmployeeReport(const vector<Order>& orders) {
    cout << "\n--- Employee Report for " << name << " (" << userID << ") ---" << endl;

    int completed = 0, pending = 0;
    string reportData = "Order ID,Customer,Status,Items\n";

    for (const auto& order : orders) {
        if (order.getAssignedEmployeeID() == userID) {
            reportData += order.getOrderID() + "," +
                         order.getCustomerName() + "," +
                         order.getStatusString() + "," +
                         to_string(order.getItems().size()) + "\n";

            if (order.getStatus() == OrderStatus::COMPLETED) completed++;
            else pending++;
        }
    }

    cout << "Completed Orders: " << completed << endl;
    cout << "Pending Orders:   " << pending << endl;
    cout << "Report data ready for export." << endl;
}