#ifndef LISTE_H
#define LISTE_H

#include"vehicules.h"
#include"reservation.h"

typedef enum typeListe{
	VEHICULE, RESERVATION, CLIENT
}typeListe;

union datas{
	vehicules vehicule;
	reservations reservation;
	clients client;
};

typedef struct liste{
	int type;
	union datas data;
	struct liste *suivant;
}liste;

liste* lireListe(int i);
void afficheListe(liste* lliste);
void lireListeT(void);
liste *cherchePrecedentVoiture(char* n,liste * ptrtete);
int superieurTest(char * chaine1,char* chaine2);
liste* ajouteVehiculeListe(liste* new,liste ** tete);
liste* ajouteReservation(liste* new, liste ** tete);
vehicules* detectVoiture(liste* tete, char immat[10]);

vehicules initialiseNullV();
clients initialiseNullC();
liste *cherchePrecedentClient(char * n,liste * ptrtete);
liste* ajouteClientListe(liste* new,liste ** tete);
liste* lireListeReservation(liste * ptrteteClient,liste * ptreTeteVoiture);
void getListeReservation(FILE* file, liste** tete,liste * ptrteteClient,liste * ptreTeteVoiture);
int CalcultailleChaine(liste *tete);
clients* detectClient(liste* tete, long int num);

#endif
