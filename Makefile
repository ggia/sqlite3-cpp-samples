all: 
	g++ connect_db.cpp -l sqlite3 -o connect_db

clean: 
	rm connect_db new.db
