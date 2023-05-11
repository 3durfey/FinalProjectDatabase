/*
 * Author: Peter Durfey
 * Class: DatabaseSystems
 * Assignment: M05 Lecture Activity 1
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "sqlite3.h"

using namespace std;

string tableNames[5];
int tableIncrement = 0;
bool tableChosen = false;
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
         cout << argv[i] << endl;
      }
   }
   return 0;
}
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
   if (rc != SQLITE_OK)
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   sqlite3_close(db);
   return rc;
};
void addCustomerInfo()
{
   int id, paymentId;
   int ints[2];
   string strings[5];
   string intNames[2] = {"id", "payment id"};
   string stringNames[5] = {"first name", "last name", "address", "city", "state"};

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
   string sql = "INSERT INTO 'customerInfo' VALUES (" + to_string(ints[0]) + ", '" + strings[0] + "', '" + strings[1] + "', '" + strings[2] + "', '" + strings[3] + "', '" + strings[4] + "', " + to_string(ints[1]) + ");";
   cout << sql << endl;
   executeStatement(sql);
}
int customerInfo(string action)
{
   if (action == "INSERT")
   {
      addCustomerInfo();
   }

   return 0;
};
void orderDetails(string action)
{
   cout << "orderDetails " << action << endl;
}

void orderItems(string action)
{
   cout << "orderItems " << action << endl;
}

void paymentInfo(string action)
{
   cout << "paymentInfo " << action << endl;
}

void productInfo(string action)
{
   cout << "productInfo " << action << endl;
}
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
int main()
{
   int choice;
   string action;
   cout << "Enter 1 to add data, 2 to update, or 3 to delete data: ";
   cin >> choice;
   switch (choice)
   {
   case 1:
      action = "INSERT";
      break;
   case 2:
      action = "UPDATE";
      break;
   case 3:
      action = "DELETE";
      break;
   }
   cout << endl;
   int chosenTable = chooseTable();
   cout << chosenTable << endl;
   switch (chosenTable)
   {
   case 4:
      customerInfo(action);
      break;
   case 1:
      orderDetails(action);
      break;
   case 2:
      orderItems(action);
      break;
   case 3:
      paymentInfo(action);
      break;
   case 0:
      productInfo(action);
      break;
   }
}