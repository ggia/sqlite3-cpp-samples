#include <iostream>
#include <sqlite3.h> 

using std::cerr; 
using std::endl;

int main(int argc, char* argv[]) {
   sqlite3 *db;
   int rc;

   rc = sqlite3_open("new.db", &db);

   if (rc) {
      cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
      return 0;
   }else{
      cerr << "Opened new.db database successfully" << endl;
   }

   sqlite3_close(db);

   return 1;
}
