voiture: main.o vehicules.o gestionListe.o chaine.o
	gcc -o voiture main.o vehicules.o gestionListe.o chaine.o

vehicules.o: vehicules.c vehicules.h chaine.h
	gcc -c -Wall vehicules.c
	
chaine.o: chaine.c
	gcc -c -Wall chaine.c
	
gestionListe.o: gestionListe.c vehicules.h gestionListe.h
	gcc -c -Wall gestionListe.c

main.o: main.c vehicules.h
	gcc -c -Wall main.c
