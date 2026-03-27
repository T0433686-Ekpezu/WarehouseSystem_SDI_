#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "Product.h"
#include "Order.h"
using namespace std;

//Forward declaration to avoid circular dependency
class Employee;

class FileHandler {
private:
    string productsFile;
    string employeesFile;
    string ordersFile;

public:
    FileHandler(string prodFile = "products.csv",
                string empFile = "employees.csv",
                string ordFile = "orders.csv");

    //Product file operations
    vector<Product> loadProducts();
    void saveProducts(const vector<Product>& products);

    //Employee file operations
    void loadEmployees(vector<Employee>& employees);
    void saveEmployees(const vector<Employee>& employees);

    //Order file operations
    vector<Order> loadOrders();
    void saveOrders(const vector<Order>& orders);

    //Report export
    void exportToCSV(const string& data, const string& filename);

    //Utility
    bool fileExists(const string& filename);
};

#endif