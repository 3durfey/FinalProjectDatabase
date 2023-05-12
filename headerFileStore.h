#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;
string tableNames[5];
int tableIncrement = 0;
bool tableChosen = false;
// callback function for sqlite3
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    if (!tableChosen)
    {
        for (i = 0; i < argc; i++)
        {
            tableNames[tableIncrement] = argv[i];
            tableIncrement++;
            if (tableIncrement == 5)
                tableChosen = true;
        }
    }
    else
    {
        for (i = 0; i < argc; i++)
        {
            printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }
    }
    return 0;
}
// execute statement to execute sqlite statements
int executeStatement(string sql)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    /* Open database */
    rc = sqlite3_open("store_durfey.db", &db);
    if (rc)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return (0);
    }
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);
    if (rc != 0)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return rc;
};
// add customer info
void addCustomerInfo()
{
    int id, paymentId;
    int ints[2];
    string strings[7];
    string intNames[2] = {"id", "payment id"};
    string stringNames[7] = {"first name", "last name", "address", "city", "state", "expiration date", "CVC code"};

    string firstName, lastName, address, city, state;
    for (int x = 0; x < 2; x++)
    {
        cout << "Enter value for " << intNames[x] << ": ";
        while (!(cin >> ints[x]))
        {
            cout << "Please enter a valid integer: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    for (int x = 0; x < 7; x++)
    {
        cout << "Enter value for " << stringNames[x] << ": ";
        while (!(cin >> strings[x]))
        {
            cout << "Please enter a valid string" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    string sql = "INSERT INTO 'customerInfo' VALUES (" + to_string(ints[0]) + ", '" + strings[0] + "', '" + strings[1] + "', '" + strings[2] + "', '" + strings[3] + "', '" + strings[4] + "', " + to_string(ints[1]) + ");";
    executeStatement(sql);
    sql = "INSERT INTO 'paymentInfo' VALUES (" + to_string(ints[1]) + ", " + to_string(ints[0]) + ", '" + strings[5] + "', " + strings[6] + ");";
    cout << sql << endl;
    executeStatement(sql);
}
// update customerInfo
void updateCustomerInfo()
{
    string stringNames[5] = {"fName", "lName", "StreetAddress", "city", "state"};
    string firstName, lastName, address, city, state, id;
    string strings[6];
    cout << "Enter ID of customer you would like to update: ";
    while (!(cin >> id))
    {
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    for (int x = 0; x < 5; x++)
    {
        cout << "Enter value for " << stringNames[x] << ": ";
        while (!(cin >> strings[x]))
        {
            cout << "Please enter a valid string" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    string sql = "UPDATE 'customerInfo' SET " +
                 stringNames[0] + " = '" + strings[0] + "', " +
                 stringNames[1] + " = '" + strings[1] + "', " +
                 stringNames[2] + " = '" + strings[2] + "', " +
                 stringNames[3] + " = '" + strings[3] + "', " +
                 stringNames[4] + " = '" + strings[4] + "' WHERE customerId = " + id + ";";
    executeStatement(sql);
}

void addOrderDetails()
{
    string customerId, orderNumber;
    cout << "Enter customer Id: ";
    cin >> customerId;
    cout << endl;
    cout << "Enter order number: ";
    cin >> orderNumber;
    string sql = "INSERT INTO 'orderDetails' VALUES (" + customerId + ", " + orderNumber + ");";
    executeStatement(sql);
}
void updateOrderDetails()
{
    string customerId, orderNumber;
    cout << "Enter order number you would like to modify: ";
    cin >> orderNumber;
    cout << endl;
    cout << "Enter new customer Id: ";
    cin >> customerId;
    string sql = "UPDATE 'orderDetails' SET customerId =" + customerId + " WHERE orderNumber = " + orderNumber + ";";
    executeStatement(sql);
}
void updateOrderItems()
{
    string productId, orderProductId, orderNum;
    cout << "Enter order product ID you would like to modify: ";
    cin >> orderProductId;
    cout << "Enter new product ID: ";
    cin >> productId;
    cout << "Enter new order number: ";
    cin >> orderNum;
    string sql = "UPDATE 'orderItems' SET productId = " + productId + ", orderNumber = " + orderNum + " WHERE orderProductId = " + orderProductId + ";";
    executeStatement(sql);
}

void addOrderItems()
{
    string productId, orderId, orderNum;
    cout << "Enter product ID: ";
    cin >> productId;
    cout << "Enter order ID: ";
    cin >> orderId;
    cout << "Enter order number: ";
    cin >> orderNum;
    string sql = "INSERT INTO 'OrderItems' VALUES (" + productId + ", " + orderId + ", " + orderNum + ");";
    executeStatement(sql);
}
void updatePaymentInfo()
{
    string paymentId, customerId, CVC, expDate;
    cout << "Enter payment ID that you would like to update: ";
    cin >> paymentId;
    cout << "Enter new customer ID: ";
    cin >> customerId;
    cout << "Enter new CVC code: ";
    cin >> CVC;
    cout << "Enter new expiration date: ";
    cin >> expDate;
    string sql = "UPDATE 'paymentInfo' SET customerId = " + customerId + ", CVC = " + CVC + ", expDate = " + expDate + " WHERE paymentId = " + paymentId + ";";
    executeStatement(sql);
}

void addPaymentInfo()
{
    string paymentId, customerId, CVC, expDate;
    cout << "Enter payment ID: ";
    cin >> paymentId;
    cout << "Enter customer ID: ";
    cin >> customerId;
    cout << "Enter CVC code: ";
    cin >> CVC;
    cout << "Enter expiration date: ";
    cin >> expDate;
    string sql = "INSERT INTO 'paymentInfo' VALUES (" + paymentId + ", " + customerId + ", '" + expDate + "', " + CVC + ");";
    executeStatement(sql);
}
void addProductInfo()
{
    string ID, weight, instockNum, cost, itemType;
    cout << "Enter product ID: ";
    cin >> ID;
    cout << "Enter weight: ";
    cin >> weight;
    cout << "Enter number of items in stock: ";
    cin >> instockNum;
    cout << "Enter cost of each item: ";
    cin >> cost;
    cout << "Enter type of item: ";
    cin >> itemType;
    string sql = "INSERT INTO 'productInfo' VALUES (" + ID + ", " + weight + ", " + instockNum + ", " + cost + ", '" + itemType + "');";
    executeStatement(sql);
}
void updateProductInfo()
{
    string ID, weight, instockNum, cost, itemType;
    cout << "Enter product ID you would like to update: ";
    cin >> ID;
    cout << "Enter new weight: ";
    cin >> weight;
    cout << "Enter new number of items in stock: ";
    cin >> instockNum;
    cout << "Enter new cost of each item: ";
    cin >> cost;
    cout << "Enter new type of item: ";
    cin >> itemType;
    string sql = "UPDATE 'productInfo' SET weight = " + weight + ", instockNumber = " + instockNum + ", cost = " + cost + ", itemType = '" + itemType + "' WHERE productId = " + ID + ";";
    executeStatement(sql);
}
// menu for finding which table user would like to modif
int chooseTable()
{
    int chose;
    int result = executeStatement("SELECT name FROM sqlite_master WHERE type='table';");
    cout << "Choose the table you would like to modify from the following list: " << endl;
    for (int x = 0; x < 5; x++)
    {
        cout << "press " << x << " for " << tableNames[x] << endl;
    }
    cin >> chose;
    return chose;
}

int customerInfo(string action)
{
    if (action == "INSERT")
    {
        addCustomerInfo();
    }
    else if (action == "DELETE")
    {
        string id;
        cout << "Enter customer ID you would like to delete: ";
        cin >> id;
        string sql = "DELETE FROM 'customerInfo' WHERE customerId=" + id + ";";
        executeStatement(sql);
    }
    else if (action == "SELECT")
    {
        string id;
        cout << "Enter customer ID to view: ";
        cin >> id;
        string sql = "SELECT * FROM 'customerInfo' WHERE customerId = " + id + ";";
        executeStatement(sql);
    }
    else
    {
        updateCustomerInfo();
    }

    return 0;
};
void orderDetails(string action)
{
    if (action == "INSERT")
    {
        addOrderDetails();
    }
    else if (action == "DELETE")
    {
        string num;
        cout << "Enter order number you would like to delete: ";
        cin >> num;
        string sql = "DELETE FROM 'orderDetails' WHERE orderNumber=" + num + ";";
        executeStatement(sql);
    }
    else if (action == "SELECT")
    {
        string id;
        cout << "Enter order number to view: ";
        cin >> id;
        string sql = "SELECT * FROM 'orderDetails' WHERE 'orderNumber = " + id + ";";
        executeStatement(sql);
    }
    else
    {
        updateOrderDetails();
    }
}

void orderItems(string action)
{
    if (action == "INSERT")
    {
        addOrderItems();
    }
    else if (action == "DELETE")
    {
        string id;
        cout << "Enter order product ID you would like to delete: ";
        cin >> id;
        string sql = "DELETE FROM 'orderItems' WHERE orderProductId=" + id + ";";
        executeStatement(sql);
    }
    else if (action == "SELECT")
    {
        string id;
        cout << "Enter order ID to view: ";
        cin >> id;
        string sql = "SELECT * FROM 'orderItems' WHERE orderProductId = " + id + ";";
        executeStatement(sql);
    }
    else
    {
        updateOrderItems();
    }
}

void paymentInfo(string action)
{
    if (action == "INSERT")
    {
        addPaymentInfo();
    }
    else if (action == "DELETE")
    {
        string id;
        cout << "Enter payment ID you would like to delete: ";
        cin >> id;
        string sql = "DELETE FROM 'paymentInfo' WHERE paymentId=" + id + ";";
        executeStatement(sql);
    }
    else if (action == "SELECT")
    {
        string id;
        cout << "Enter payment ID to view: ";
        cin >> id;
        string sql = "SELECT * FROM 'paymentInfo' WHERE paymentId = " + id + ";";
        executeStatement(sql);
    }
    else
    {
        updatePaymentInfo();
    }
}

void productInfo(string action)
{
    if (action == "INSERT")
    {
        addProductInfo();
    }
    else if (action == "DELETE")
    {
        string id;
        cout << "Enter product ID you would like to delete: ";
        cin >> id;
        string sql = "DELETE FROM 'productInfo' WHERE productId=" + id + ";";
        executeStatement(sql);
    }
    else if (action == "SELECT")
    {
        string id;
        cout << "Enter product ID to view: ";
        cin >> id;
        string sql = "SELECT * FROM 'productInfo' WHERE productId = " + id + ";";
        executeStatement(sql);
    }
    else
    {
        updateProductInfo();
    }
}
