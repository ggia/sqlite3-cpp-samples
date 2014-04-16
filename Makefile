all: 
	g++ sqlite3_ex.cpp -o sqlite3_ex -l sqlite3
clean: 
	rm new.db sqlite3_ex
