#include <iostream>
#include "sqlite3.h"

using namespace std;

string arr[3] = {"tt", "tse", "tese"};

void func(int *arr)
{
    arr[0] = 3;
}
int main()
{
    sqlite3 *mydb;
    int database = sqlite3_open("SaleCo.db", &mydb);
    if (database)
    {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(mydb));
        return 0;
    }
    else
    {
        fprintf(stdout, "Opened database successfully\n");
    }

    sqlite3_stmt *stmt;
    const char *sql = "SELECT ID, Name FROM User";
    int rc = sqlite3_prepare_v2(mydb, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK)
    {
        cout << "error: " << sqlite3_errmsg(mydb) << endl;
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const char *name = sqlite3_column_text(stmt, 1);
    }
    if (rc != SQLITE_DONE)
    {
        cout << "error: ", sqlite3_errmsg(mydb) << endl;
    }
    sqlite3_finalize(stmt);
}
