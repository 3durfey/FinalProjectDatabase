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

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   for (i = 0; i < argc; i++)
   {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char *argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   string sql;

   /* Open database */
   rc = sqlite3_open("store_durfey.db", &db);

   if (rc)
   {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return (0);
   }
   else
   {
      fprintf(stdout, "Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "SELECT * FROM 'customerInfo';";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if (rc != SQLITE_OK)
   {
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else
   {
      fprintf(stdout, "Query successful\n");
      cout << rc << endl;
   }
   sqlite3_close(db);
   return 0;
}