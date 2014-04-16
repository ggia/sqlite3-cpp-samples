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
   const char* data = "Callback function called";
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

   // Create SQL statement 
   sql = string("INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'George', 32, 'Athens', 10000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Petros', 25, 'Larissa', 7000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Mary', 23, 'Komotini', 8000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Aggelos', 45, 'Stockholm ', 15000.00 );"
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (5, 'Thanos', 43, 'Den Haag ', 17000.00 );");

   // Execute SQL statement
   rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

   if( rc != SQLITE_OK ) {
      cerr << "SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }
   else {
      cout << "Records created successfully" << endl;
   }

   // Create SQL statement 
   sql = "SELECT * from COMPANY";

   // Execute SQL statement 
   rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ) {
      cerr << "SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }
   else {
      cout << "Operation dislay all done successfully" << endl;
   }

   // Create merged SQL statement 
   sql = "UPDATE COMPANY set SALARY = 25000.00 where NAME='Thanos'; " \
         "SELECT * from COMPANY";

   // Execute SQL statement 
   rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ) {
      cerr << "SQL error: " <<  zErrMsg;
      sqlite3_free(zErrMsg);
   } 
   else {
      cout << "Operation update done successfully" << endl;
   }

   // Create merged SQL statement */
   sql = "DELETE from COMPANY where SALARY > 10000.00; " \
         "SELECT * from COMPANY";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      cerr << "SQL error: " << zErrMsg << endl;
      sqlite3_free(zErrMsg);
   }
   else {
      cout << "Delete Operation done successfully" << endl;
   }

   // close database
   sqlite3_close(db);

   return 0;
}
