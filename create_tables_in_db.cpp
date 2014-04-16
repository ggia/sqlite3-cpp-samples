#include <iostream>
#include <string>
#include <sqlite3.h> 

using std::cout;
using std::cerr;
using std::endl;
using std::string;

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){

   for(int i=0; i<argc; i++) {
      cout << azColName[i] << " = " << string(argv[i] ? argv[i] : "NULL") << endl;
   }

   cout << endl;

   return 0;
}

int main(int argc, char* argv[]) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int  rc;
   string sql;

   // Open database 
   rc = sqlite3_open("new.db", &db);
   if (rc) {
      cerr <<  "Can't open database: " <<  sqlite3_errmsg(db) << endl;;
      return 0;
   }
   else {
      cout << "Opened database successfully" << endl;
   }

   // Create SQL statement
   sql = string("CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );");

   // Execute SQL statement 
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ){
      cerr << "SQL error: "<<  zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }
   else {
      cout << "Table created successfully" << endl;
   }

   // close database
   sqlite3_close(db);

   return 0;
}
