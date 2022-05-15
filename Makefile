CC=g++
CFLAGS=-Wall -Wextra

# Make only runs the first rule if you call it w/o any arguments.
All: Ausdruecke Datentypen Zahlenraten Gleichungen

# Backslash used to escape the whiteline (make doesn't like it when you surround dependencies with quotes)
Ausdruecke: Week1\1.1\ Ausdruecke.cpp
	$(CC) -o Week1\Ausdruecke.exe "Week1\1.1 Ausdruecke.cpp" $(CFLAGS)

Datentypen: Week1\1.2\ Datentypen.cpp
	$(CC) -o Week1\Datentypen.exe "Week1\1.2 Datentypen.cpp" $(CFLAGS)

Zahlenraten: Week2\2.1\ Zahlenraten.cpp
	$(CC) -o Week2\Zahlenraten.exe "Week2\2.1 Zahlenraten.cpp" $(CFLAGS)

Gleichungen: Week2\2.2\ Gleichungen.cpp
	$(CC) -o Week2\Gleichungen.exe "Week2\2.2 Gleichungen.cpp" $(CFLAGS)