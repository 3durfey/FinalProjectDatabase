/*
 * Author: Peter Durfey
 * Class: DatabaseSystems
 * Assignment: M05 Lecture Activity 1
 */

#include <iostream>
#include <string>
#include <iomanip>
#include "headerFileStore.h"
using namespace std;

int main()
{
   int choice;
   string action;
   cout << "Enter 0 to view data, 1 to add data, 2 to update, or 3 to delete data: ";
   cin >> choice;
   switch (choice)
   {
   case 0:
      action = "SELECT";
      break;
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
   switch (chosenTable)
   {
   case 4:
      customerInfo(action);
      break;
   case 2:
      orderDetails(action);
      break;
   case 1:
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