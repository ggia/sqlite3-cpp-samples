all: 
	g++ connect_db.cpp -l sqlite3 -o connect_db
	g++ create_tables_in_db.cpp -o create_tables_in_db -l sqlite3
clean: 
	rm connect_db new.db create_tables_in_db
