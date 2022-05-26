CC=g++
CFLAGS=-std=c++17 -pedantic -Wall -Wextra
LDFLAGS=
EXEC=exec

all: $(EXEC)

exec: bin/row.o bin/csv_parser.o bin/character.o bin/question.o bin/main.o
	$(CC) -o $@ $^ $(LDFLAGS)
bin/row.o: source/row.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
bin/csv_parser.o: source/csv_parser.cpp include/row.hpp include/question.hpp include/character.hpp
	$(CC) -o $@ -c $< $(CFLAGS)
bin/character.o: source/character.cpp include/question.hpp include/row.hpp
	$(CC) -o $@ -c $< $(CFLAGS)
bin/question.o: source/question.cpp include/character.hpp include/row.hpp
	$(CC) -o $@ -c $< $(CFLAGS)
bin/main.o: source/main.cpp include/question.hpp include/character.hpp include/csv_parser.hpp include/row.hpp
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o core
mrproper: clean
	rm -f $(EXEC)