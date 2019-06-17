voiture: main.o vehicules.o
	gcc -o voiture main.o vehicules.o

vehicules.o: vehicules.c vehicules.h
	gcc -c -Wall vehicules.c

main.o: main.c vehicules.h
	gcc -c -Wall main.c
