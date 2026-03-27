#include "Manager.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;

Manager::Manager(string id, string name, string pw)
    : User(id, name, pw) {}

//Override showMenu
void Manager::showMenu() {
    cout << "\n======================================" << endl;
    cout << "   MANAGER MENU - Welcome " << name << endl;
    cout << "======================================" << endl;
    cout << "1.  Add Product" << endl;
    cout << "2.  View Products" << endl;
    cout << "3.  Edit Product" << endl;
    cout << "4.  Add Employee" << endl;
    cout << "5.  View Employees" << endl;
    cout << "6.  Edit Employee" << endl;
    cout << "7.  Create Order" << endl;
    cout << "8.  View Orders" << endl;
    cout << "9.  Edit Order" << endl;
    cout << "10. Assign Order" << endl;
    cout << "11. Generate Inventory Report" << endl;
    cout << "12. Generate Completed Orders Report" << endl;
    cout << "13. Generate Pending Orders Report" << endl;
    cout << "14. Logout" << endl;
    cout << "======================================" << endl;
    cout << "Enter choice: ";
}

//PRODUCT MANAGEMENT

//Add a new product to inventory
void Manager::addProduct(Inventory& inv) {
    string id, name, location;
    int qty;

    cout << "\n--- Add New Product ---" << endl;

    cout << "Enter Product ID: ";
    getline(cin, id);

    //Check for duplicate ID
    if (inv.productExists(id)) {
        cout << "Error: Product ID " << id << " already exists." << endl;
        return;
    }

    cout << "Enter Product Name: ";
    getline(cin, name);

    cout << "Enter Quantity: ";
    while (!(cin >> qty) || qty < 0) {
        cout << "Error: Please enter a valid positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();

    cout << "Enter Location (e.g., Shelf B3): ";
    getline(cin, location);

    //Validate all fields are not empty
    if (id.empty() || name.empty() || location.empty()) {
        cout << "Error: All fields are required." << endl;
        return;
    }

    Product newProduct(id, name, qty, location);
    inv.addProduct(newProduct);
    cout << "Product '" << name << "' added successfully!" << endl;
}

//View all products with sorting options
void Manager::viewProducts(Inventory& inv) {
    cout << "\n--- View Products ---" << endl;
    cout << "Sort by: 1. ID  2. Name  3. Quantity  4. No sorting" << endl;
    cout << "Choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice) {
        case 1: inv.sortByID(); break;
        case 2: inv.sortByName(); break;
        case 3: inv.sortByQuantity(); break;
        case 4: break;
        default: break;
    }

    inv.displayAll();
}

//Edit an existing product
void Manager::editProduct(Inventory& inv) {
    cout << "\n--- Edit Product ---" << endl;
    cout << "Enter Product ID to edit: ";
    string id;
    getline(cin, id);
    inv.editProduct(id);
}

//EMPLOYEE MANAGEMENT

//Register a new employee
void Manager::addEmployee(vector<Employee>& employees) {
    string id, empName, pw;

    cout << "\n--- Register New Employee ---" << endl;

    cout << "Enter Employee ID: ";
    getline(cin, id);

    //Check for duplicate ID
    for (const auto& emp : employees) {
        if (emp.getUserID() == id) {
            cout << "Error: Employee ID " << id << " already exists." << endl;
            return;
        }
    }

    cout << "Enter Employee Name: ";
    getline(cin, empName);

    cout << "Enter Password: ";
    getline(cin, pw);

    if (id.empty() || empName.empty() || pw.empty()) {
        cout << "Error: All fields are required." << endl;
        return;
    }

    Employee newEmp(id, empName, pw);
    employees.push_back(newEmp);
    cout << "Employee '" << empName << "' registered successfully!" << endl;
}

//View all employees
void Manager::viewEmployees(const vector<Employee>& employees) {
    cout << "\n--- All Employees ---" << endl;
    if (employees.empty()) {
        cout << "No employees registered." << endl;
        return;
    }

    cout << left << setw(15) << "Employee ID"
         << setw(25) << "Name" << endl;
    cout << string(40, '-') << endl;

    for (const auto& emp : employees) {
        cout << left << setw(15) << emp.getUserID()
             << setw(25) << emp.getName() << endl;
    }
    cout << "\nTotal employees: " << employees.size() << endl;
}

//Edit employee details (FR-10)
void Manager::editEmployee(vector<Employee>& employees) {
    cout << "\n--- Edit Employee ---" << endl;
    cout << "Enter Employee ID to edit: ";
    string id;
    getline(cin, id);

    for (auto& emp : employees) {
        if (emp.getUserID() == id) {
            cout << "Current name: " << emp.getName() << endl;
            cout << "Enter new name (or press Enter to keep): ";
            string newName;
            getline(cin, newName);
            if (!newName.empty()) {
                emp.setName(newName);
                cout << "Employee name updated successfully." << endl;
            }
            return;
        }
    }
    cout << "Error: Employee " << id << " not found." << endl;
}

//ORDER MANAGEMENT

//Create a new customer order
void Manager::createOrder(vector<Order>& orders, Inventory& inv) {
    string orderID, customer;

    cout << "\n--- Create New Order ---" << endl;

    cout << "Enter Order ID: ";
    getline(cin, orderID);

    // Check for duplicate order ID
    for (const auto& ord : orders) {
        if (ord.getOrderID() == orderID) {
            cout << "Error: Order ID " << orderID << " already exists." << endl;
            return;
        }
    }

    cout << "Enter Customer Name: ";
    getline(cin, customer);

    if (orderID.empty() || customer.empty()) {
        cout << "Error: All fields are required." << endl;
        return;
    }

    Order newOrder(orderID, customer);

    //Add items to the order
    cout << "\nAdd items to the order (enter 'done' to finish):" << endl;
    while (true) {
        string prodID;
        cout << "\nProduct ID (or 'done'): ";
        getline(cin, prodID);

        if (prodID == "done" || prodID == "DONE") break;

        // Check product exists
        Product* product = inv.findProductByID(prodID);
        if (product == nullptr) {
            cout << "Error: Product " << prodID << " not found. Try again." << endl;
            continue;
        }

        int qty;
        cout << "Quantity: ";
        while (!(cin >> qty) || qty <= 0) {
            cout << "Error: Please enter a valid positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();

        OrderItem item(prodID, product->getName(), qty);
        newOrder.addItem(item);
        cout << "Added: " << product->getName() << " x " << qty << endl;
    }

    if (newOrder.getItems().empty()) {
        cout << "Error: Order must have at least one item." << endl;
        return;
    }

    orders.push_back(newOrder);
    cout << "\nOrder " << orderID << " created successfully!" << endl;
    newOrder.displayDetailed();
}

//Edit an existing order
void Manager::editOrder(vector<Order>& orders) {
    cout << "\n--- Edit Order ---" << endl;
    cout << "Enter Order ID to edit: ";
    string id;
    getline(cin, id);

    for (auto& order : orders) {
        if (order.getOrderID() == id) {
            if (order.getStatus() == OrderStatus::COMPLETED) {
                cout << "Error: Cannot edit a completed order." << endl;
                return;
            }

            cout << "Current order details:" << endl;
            order.displayDetailed();

            cout << "1. Change Customer Name" << endl;
            cout << "2. Add Item" << endl;
            cout << "3. Remove Item" << endl;
            cout << "4. Edit Item Quantity" << endl;
            cout << "5. Cancel" << endl;
            cout << "Choice: ";

            int choice;
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: {
                    cout << "Enter new customer name: ";
                    string newName;
                    getline(cin, newName);
                    if (!newName.empty()) {
                        order.setCustomerName(newName);
                        cout << "Customer name updated." << endl;
                    }
                    break;
                }
                case 2: {
                    cout << "Enter Product ID: ";
                    string prodID;
                    getline(cin, prodID);
                    cout << "Enter Product Name: ";
                    string prodName;
                    getline(cin, prodName);
                    int qty;
                    cout << "Enter Quantity: ";
                    cin >> qty;
                    cin.ignore();
                    order.addItem(OrderItem(prodID, prodName, qty));
                    cout << "Item added." << endl;
                    break;
                }
                case 3: {
                    cout << "Enter Product ID to remove: ";
                    string prodID;
                    getline(cin, prodID);
                    order.removeItem(prodID);
                    break;
                }
                case 4: {
                    cout << "Enter Product ID: ";
                    string prodID;
                    getline(cin, prodID);
                    int newQty;
                    cout << "Enter new quantity: ";
                    cin >> newQty;
                    cin.ignore();
                    order.editItemQuantity(prodID, newQty);
                    break;
                }
                case 5:
                    cout << "Edit cancelled." << endl;
                    break;
            }
            return;
        }
    }
    cout << "Error: Order " << id << " not found." << endl;
}

//View all orders (FR-13)
void Manager::viewOrders(const vector<Order>& orders) {
    cout << "\n--- All Orders ---" << endl;
    if (orders.empty()) {
        cout << "No orders in the system." << endl;
        return;
    }

    cout << left << setw(12) << "Order ID"
         << setw(20) << "Customer"
         << setw(14) << "Status"
         << setw(12) << "Assigned To"
         << "Items" << endl;
    cout << string(65, '-') << endl;

    for (const auto& order : orders) {
        order.display();
    }
    cout << "\nTotal orders: " << orders.size() << endl;

    //Ask if user wants to see details
    cout << "\nView details for an order? (y/n): ";
    char ch;
    cin >> ch;
    cin.ignore();
    if (ch == 'y' || ch == 'Y') {
        cout << "Enter Order ID: ";
        string id;
        getline(cin, id);
        for (const auto& order : orders) {
            if (order.getOrderID() == id) {
                order.displayDetailed();
                return;
            }
        }
        cout << "Order not found." << endl;
    }
}

//Assign an order to an employee (FR-15, FR-16)
void Manager::assignOrder(vector<Order>& orders, vector<Employee>& employees, Inventory& inv) {
    cout << "\n--- Assign Order to Employee ---" << endl;

    cout << "Enter Order ID: ";
    string orderID;
    getline(cin, orderID);

    // Find the order
    Order* targetOrder = nullptr;
    for (auto& order : orders) {
        if (order.getOrderID() == orderID) {
            targetOrder = &order;
            break;
        }
    }

    if (targetOrder == nullptr) {
        cout << "Error: Order " << orderID << " not found." << endl;
        return;
    }

    if (targetOrder->getStatus() != OrderStatus::CREATED) {
        cout << "Error: Order is already " << targetOrder->getStatusString()
             << ". Only CREATED orders can be assigned." << endl;
        return;
    }

    //Checks stock availability
    cout << "\nValidating stock levels..." << endl;
    if (!inv.checkStock(targetOrder->getItems())) {
        cout << "Error: Cannot assign order — insufficient stock." << endl;
        return;
    }
    cout << "Stock validation passed!" << endl;

    //Show available employees
    cout << "\nAvailable employees:" << endl;
    viewEmployees(employees);

    cout << "\nEnter Employee ID to assign: ";
    string empID;
    getline(cin, empID);

    //Find the employee
    Employee* targetEmp = nullptr;
    for (auto& emp : employees) {
        if (emp.getUserID() == empID) {
            targetEmp = &emp;
            break;
        }
    }

    if (targetEmp == nullptr) {
        cout << "Error: Employee " << empID << " not found." << endl;
        return;
    }

    //Assign the order
    targetOrder->setAssignedEmployee(empID);
    targetOrder->setStatus(OrderStatus::ASSIGNED);
    targetEmp->addAssignedOrder(orderID);

    cout << "\nOrder " << orderID << " assigned to " << targetEmp->getName()
         << " (" << empID << ") successfully!" << endl;
}

//REPORT GENERATION

//Generate inventory report (FR-18)
void Manager::generateInventoryReport(Inventory& inv) {
    cout << "\n--- Inventory Report ---" << endl;
    inv.displayAll();

    //Build CSV data
    string csvData = "Product ID,Name,Quantity,Location\n";
    for (const auto& p : inv.getAllProducts()) {
        csvData += p.getProductID() + "," + p.getName() + "," +
                   to_string(p.getQuantity()) + "," + p.getLocation() + "\n";
    }

    //Write to file
    ofstream file("inventory_report.csv");
    if (file.is_open()) {
        file << csvData;
        file.close();
        cout << "\nReport exported to: inventory_report.csv" << endl;
    } else {
        cout << "Error: Could not create report file." << endl;
    }
}

//Generate completed orders report
void Manager::generateCompletedOrdersReport(const vector<Order>& orders) {
    cout << "\n--- Completed Orders Report ---" << endl;

    string csvData = "Order ID,Customer,Assigned To,Items\n";
    int count = 0;

    for (const auto& order : orders) {
        if (order.getStatus() == OrderStatus::COMPLETED) {
            order.display();
            csvData += order.getOrderID() + "," + order.getCustomerName() + "," +
                       order.getAssignedEmployeeID() + "," +
                       to_string(order.getItems().size()) + "\n";
            count++;
        }
    }

    cout << "\nTotal completed orders: " << count << endl;

    ofstream file("completed_orders_report.csv");
    if (file.is_open()) {
        file << csvData;
        file.close();
        cout << "Report exported to: completed_orders_report.csv" << endl;
    }
}

//Generate pending orders report
void Manager::generatePendingOrdersReport(const vector<Order>& orders) {
    cout << "\n--- Pending Orders Report ---" << endl;

    string csvData = "Order ID,Customer,Status,Assigned To,Items\n";
    int count = 0;

    for (const auto& order : orders) {
        if (order.getStatus() != OrderStatus::COMPLETED) {
            order.display();
            csvData += order.getOrderID() + "," + order.getCustomerName() + "," +
                       order.getStatusString() + "," + order.getAssignedEmployeeID() + "," +
                       to_string(order.getItems().size()) + "\n";
            count++;
        }
    }

    cout << "\nTotal pending orders: " << count << endl;

    ofstream file("pending_orders_report.csv");
    if (file.is_open()) {
        file << csvData;
        file.close();
        cout << "Report exported to: pending_orders_report.csv" << endl;
    }
}