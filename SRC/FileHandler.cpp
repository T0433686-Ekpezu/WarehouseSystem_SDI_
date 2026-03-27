#include "FileHandler.h"
#include "Employee.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

FileHandler::FileHandler(string prodFile, string empFile, string ordFile)
    : productsFile(prodFile), employeesFile(empFile), ordersFile(ordFile) {}

//PRODUCT FILE OPERATIONS

//Load products from CSV file
vector<Product> FileHandler::loadProducts() {
    vector<Product> products;
    ifstream file(productsFile);

    if (!file.is_open()) {
        cout << "Note: No existing products file found. Starting fresh." << endl;
        return products;
    }

    string line;
    getline(file, line); //Skip header row

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, name, qtyStr, location;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, qtyStr, ',');
        getline(ss, location, ',');

        try {
            int qty = stoi(qtyStr);
            products.push_back(Product(id, name, qty, location));
        } catch (const exception& e) {
            cout << "Warning: Skipping invalid product line: " << line << endl;
        }
    }

    file.close();
    cout << "Loaded " << products.size() << " products from file." << endl;
    return products;
}

//Save products to CSV file
void FileHandler::saveProducts(const vector<Product>& products) {
    ofstream file(productsFile);

    if (!file.is_open()) {
        cout << "Error: Could not save products file." << endl;
        return;
    }

    file << "ProductID,Name,Quantity,Location" << endl;
    for (const auto& p : products) {
        file << p.getProductID() << ","
             << p.getName() << ","
             << p.getQuantity() << ","
             << p.getLocation() << endl;
    }

    file.close();
}

//EMPLOYEE FILE OPERATIONS

//Load employees from CSV file
void FileHandler::loadEmployees(vector<Employee>& employees) {
    ifstream file(employeesFile);

    if (!file.is_open()) {
        cout << "Note: No existing employees file found. Starting fresh." << endl;
        return;
    }

    string line;
    getline(file, line); //Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string id, name, pw;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, pw, ',');

        employees.push_back(Employee(id, name, pw));
    }

    file.close();
    cout << "Loaded " << employees.size() << " employees from file." << endl;
}

// Save employees to CSV file
void FileHandler::saveEmployees(const vector<Employee>& employees) {
    ofstream file(employeesFile);

    if (!file.is_open()) {
        cout << "Error: Could not save employees file." << endl;
        return;
    }

    file << "EmployeeID,Name,Password" << endl;
    for (const auto& emp : employees) {
        file << emp.getUserID() << ","
             << emp.getName() << ","
             << emp.getPassword() << endl;
    }

    file.close();
}

//ORDER FILE OPERATIONS

//Load orders from CSV file
vector<Order> FileHandler::loadOrders() {
    vector<Order> orders;
    ifstream file(ordersFile);

    if (!file.is_open()) {
        cout << "Note: No existing orders file found. Starting fresh." << endl;
        return orders;
    }

    string line;
    getline(file, line); //Skip header

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string orderID, customer, statusStr, empID, itemsStr;

        getline(ss, orderID, ',');
        getline(ss, customer, ',');
        getline(ss, statusStr, ',');
        getline(ss, empID, ',');
        getline(ss, itemsStr); // Rest of line is items

        Order order(orderID, customer);
        order.setStatus(stringToOrderStatus(statusStr));
        if (!empID.empty()) {
            order.setAssignedEmployee(empID);
        }

        //Parse items
        if (!itemsStr.empty()) {
            stringstream itemStream(itemsStr);
            string itemToken;
            while (getline(itemStream, itemToken, '|')) {
                if (itemToken.empty()) continue;
                stringstream is(itemToken);
                string pID, pName, qStr;
                getline(is, pID, ':');
                getline(is, pName, ':');
                getline(is, qStr, ':');
                try {
                    int qty = stoi(qStr);
                    order.addItem(OrderItem(pID, pName, qty));
                } catch (...) {
                    //Skip invalid items
                }
            }
        }

        orders.push_back(order);
    }

    file.close();
    cout << "Loaded " << orders.size() << " orders from file." << endl;
    return orders;
}

//Save orders to CSV file
void FileHandler::saveOrders(const vector<Order>& orders) {
    ofstream file(ordersFile);

    if (!file.is_open()) {
        cout << "Error: Could not save orders file." << endl;
        return;
    }

    file << "OrderID,Customer,Status,AssignedTo,Items" << endl;
    for (const auto& order : orders) {
        file << order.getOrderID() << ","
             << order.getCustomerName() << ","
             << order.getStatusString() << ","
             << order.getAssignedEmployeeID() << ",";

        const auto& items = order.getItems();
        for (size_t i = 0; i < items.size(); i++) {
            file << items[i].getProductID() << ":"
                 << items[i].getProductName() << ":"
                 << items[i].getQuantity();
            if (i < items.size() - 1) file << "|";
        }
        file << endl;
    }

    file.close();
}

//Export report data to a CSV file
void FileHandler::exportToCSV(const string& data, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << data;
        file.close();
        cout << "Report exported to: " << filename << endl;
    } else {
        cout << "Error: Could not create report file." << endl;
    }
}

//Check if a file exists
bool FileHandler::fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}